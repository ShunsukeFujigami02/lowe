#include "funcmap.hh"

funcmap::funcmap()
{
}

void funcmap::setup()
{
  lfuncmap.insert(std::make_pair("noretro",std::make_shared<likelihoodnoretro>()));
  lfuncmap.insert(std::make_pair("onretro",std::make_shared<likelihoodonretro>()));
  lfuncmap.insert(std::make_pair("sum",std::make_shared<likelihoodsum>()));
  distancefuncmap.insert(std::make_pair("position_pmt",std::make_shared<distance_position_pmt>()));
  distancefuncmap.insert(std::make_pair("position_retro",std::make_shared<distance_position_retro>()));
  distancefuncmap.insert(std::make_pair("fly_retro",std::make_shared<distance_fly_retro>()));
  fdirmap.insert(std::make_pair("prototype_noretro",std::make_shared<fdirprototypenoretro>()));
  fdirmap.insert(std::make_pair("prototype_onretro",std::make_shared<fdirprototypeonretro>()));
  fdirmap.insert(std::make_pair("bydata_onretro",std::make_shared<fdirbydataonretro>()));
  fdirmap.insert(std::make_pair("bydata_noretro",std::make_shared<fdirbydatanoretro>()));
  afuncmap.insert(std::make_pair("prototype",std::make_shared<afuncprototype>()));
}

