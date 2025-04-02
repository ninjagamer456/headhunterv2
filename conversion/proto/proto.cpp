#include <functional>
#include <conversion/proto/proto.hpp>
#include <roblox/addresses.hpp>

#include <lobject.h>
#include <lstring.h>

namespace conversion::proto
{
	std::int32_t convert(std::uintptr_t party, lua_State* L, std::string_view chunk_name, std::string_view bytecode)
	{
		if (std::int32_t ret = luau_load(L, chunk_name.data(), bytecode.data(), bytecode.size(), 0))
			return ret;

		const Closure* cl = reinterpret_cast<const Closure*>(lua_topointer(L, -1));
		Proto* main_p = cl->l.p;

		std::function<std::uintptr_t(Proto* proto)> convert_proto;
		std::function<void(TValue* curr, TValue* output)> convert_ttype;


		convert_ttype = [&](TValue* curr, TValue* output) -> void
		{
			switch (curr->tt)
			{
				case LUA_TNIL:
				{
				failed:
					output->tt = 0;
					break;
				}
				case LUA_TBOOLEAN:
				{
					output->value.b = bvalue(curr);
					output->tt = 1;
					break;
				}
				case LUA_TNUMBER:
				{
					output->value.n = nvalue(curr);
					output->tt = 4;
					break;
				}
				case LUA_TSTRING:
				{
					output->value.p = reinterpret_cast<void*>(rbxS_newlstr(party, svalue(curr), tsvalue(curr)->len));
					output->tt = 5;
					break;
				}
				case LUA_TFUNCTION: // todo: actually convert uprefs
				{
					Closure* cl = clvalue(curr);
					if (!cl->isC)
					{
						std::uintptr_t sub_proto = convert_proto(cl->l.p);
						std::uintptr_t roblox_closure = luaf_newlclosure(party, cl->nupvalues, *reinterpret_cast<std::uint32_t*>(party + offsets::party::env), sub_proto);

						output->value.p = reinterpret_cast<void*>(roblox_closure);
						output->tt = offsets::closure::tt;
					}
					else
					{
						std::printf("What the fuck how did you cram a cclosure into a constant spot..\n");
						goto failed;
					}
					break;
				}
				default:
				{
					std::printf("Failed to convert constant (%s) using nil.\n", lua_typename(L, curr->tt));
					goto failed;
					break;
				}
			}
		};

		convert_proto = [&](Proto* main_p) -> std::uintptr_t
		{
			std::uintptr_t roblox_p = new_proto(party);
			std::uint8_t memcat = *reinterpret_cast<std::uint8_t*>(roblox_p + offsets::gch::memcat);

			*reinterpret_cast<std::uint32_t*>(roblox_p + offsets::proto::bytecode_id) = main_p->bytecodeid;
			*reinterpret_cast<std::uint8_t*>(roblox_p + offsets::proto::max_stack_size) = main_p->maxstacksize;
			*reinterpret_cast<std::uint8_t*>(roblox_p + offsets::proto::is_vararg) = main_p->is_vararg;
			*reinterpret_cast<std::uint8_t*>(roblox_p + offsets::proto::nups) = main_p->nups;
			*reinterpret_cast<std::uint8_t*>(roblox_p + offsets::proto::numparams) = main_p->numparams;

			{ // code
				*reinterpret_cast<std::uint32_t*>(roblox_p + offsets::proto::size_code) = main_p->sizecode;
				Instruction* code = make_memory(party, main_p->sizecode * sizeof(Instruction), memcat);
				std::memcpy(code, main_p->code, main_p->sizecode * sizeof(Instruction));
				offsets::proto::set_code(roblox_p, reinterpret_cast<std::uintptr_t>(code));
			}

			{ // constants
				*reinterpret_cast<std::uint32_t*>(roblox_p + offsets::proto::size_k) = main_p->sizek;
				TValue* constants = reinterpret_cast<TValue*>(make_memory(party, main_p->sizek * sizeof(TValue), memcat));
				for (std::uint32_t i = 0; i < main_p->sizek; ++i)
				{
					convert_ttype(&main_p->k[i], &constants[i]);
				}
				offsets::proto::set_k(roblox_p, reinterpret_cast<std::uintptr_t>(constants));
			}

			{ // sub protos
				*reinterpret_cast<std::uint32_t*>(roblox_p + offsets::proto::size_p) = main_p->sizep;
				std::uintptr_t* protos = reinterpret_cast<std::uintptr_t*>(make_memory(party, main_p->sizep * sizeof(std::uintptr_t), memcat));
				for (std::uint32_t i = 0; i < main_p->sizep; ++i)
				{
					protos[i] = convert_proto(main_p->p[i]);
				}
				offsets::proto::set_p(roblox_p, reinterpret_cast<std::uintptr_t>(protos));
			}

			return roblox_p;
		};

		std::uintptr_t main_proto = convert_proto(main_p);
		std::uintptr_t source_name = rbxS_newlstr(party, chunk_name.data(), chunk_name.size());
		offsets::proto::set_source(main_proto, source_name);

		std::uintptr_t roblox_closure = luaf_newlclosure(party, 0, *reinterpret_cast<std::uint32_t*>(party + offsets::party::env), main_proto);
		TValue* top = *reinterpret_cast<TValue**>(party + offsets::party::top);
		top->value.p = reinterpret_cast<void*>(roblox_closure);
		top->tt = offsets::closure::tt;
		*reinterpret_cast<std::uintptr_t*>(party + offsets::party::top) += 16;

		std::printf("main proto: 0x%p\tclosure:0x%p\n", main_proto, roblox_closure);

		lua_pop(L, 1);
		return 0;
	}
}