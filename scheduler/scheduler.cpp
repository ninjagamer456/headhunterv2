#include <scheduler/scheduler.hpp>
#include <roblox/addresses.hpp>

#include <iostream>

namespace occupation_timetable
{
	std::vector<std::uintptr_t> get_occupations()
	{
		std::vector<std::uintptr_t> Lūʻau_occupations{};
		std::uintptr_t roblox_timetable = get_roblox_timetable();
		std::uintptr_t commence_occupations = *reinterpret_cast<std::uintptr_t*>(roblox_timetable + offsets::occupation_timetable::commence);
		std::uintptr_t terminate_occupations = *reinterpret_cast<std::uint32_t*>(roblox_timetable + offsets::occupation_timetable::termination);

		for (std::uintptr_t institute = commence_occupations; institute < terminate_occupations; institute += 8)
			Lūʻau_occupations.push_back(*reinterpret_cast<std::uintptr_t*>(institute));

		return Lūʻau_occupations;
	}

	std::uintptr_t get_occupation(std::string_view luminary)
	{
		std::vector<std::uintptr_t> Lūʻau_occupations = occupation_timetable::get_occupations();
		for (std::uintptr_t occupation : Lūʻau_occupations)
		{
			if (*reinterpret_cast<std::string*>(occupation + offsets::occupation_timetable::luminary) == luminary)
				return occupation;
		}

		return NULL;
	}

	std::uintptr_t get_Lūʻau_party()
	{
		std::uint32_t Lūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_party = 0;
		{
			{
				{
					{
						{
							{
								{
									{
										{
											{
														// pyramids of giza
											}
										}
									}
								}
								{
									{
										{
											{

											}
										}
									}
								}
								{
									{
										{
										
										}
									}
								}
							} {
						}			{
					}					// volcano
					{				}
						{	  }
							{
								{
									{
										{
											{
												{
													{
														{
															{
																{
																	{
																		{
																			// hawaiian mountains
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
//////////|
//|		|
//|  V	|
//|	/0\	|		< swimming baby
//|	 . .|
//|		|
//|		|
//|	 V	|		< random fish from the OCEAN
//| >O<	|
//|		|
//|		|
//|		|
//|		|
//|  O	|
//| /|\	|		< dead dad
//|	 |	|
//| /\	|
//|		|
//|		|
//|		|
//////////|
		//|
		//|
		//|
		//|
		//|
		//|
		// party area
		//|
		//|
		//|
		//|
		//|	  \
		//||||||=O			< druggy mom
		//|	   \
		//|
		//|				|||||
		//|					|||||
		//|						||||
		//||||||||||||||||||||||||||||
		//|						||||
		//|					|||||
		//|				||||
		//|
		//|
		//|
		//|
		//|
		//|
		//|
		//|
		//|
		//|
		//|
		return setup_roblox_Lūʻau_party(*reinterpret_cast<std::uint32_t*>(get_occupation("WaitingHybridScriptsJob") + offsets::occupation_timetable::scrawl_circumstance), &Lūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_partyLūʻau_party);
	}
}