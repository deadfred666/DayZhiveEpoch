/*
* Copyright (C) 2009-2012 Rajko Stojadinovic <http://github.com/rajkosto/hive>
* Copyright (C) 2013 Blaine Palmer <https://github.com/blainepalmer/DayZhiveEpoch>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include "SqlCustomLoadoutSource.h"
#include "Database/Database.h"

#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
using boost::bad_lexical_cast;

SqlCustomLoadoutSource::SqlCustomLoadoutSource( Poco::Logger& logger, shared_ptr<Database> db ) : SqlDataSource(logger,db)
{
}

SqlCustomLoadoutSource::~SqlCustomLoadoutSource() {}

Sqf::Value SqlCharDataSource::fetchDefaultLoadout( int serverId )
{
	Sqf::Parameters retVal;

	auto defLoadoutRes = getDB()->queryParams(
		"SELECT `Inventory`, `Backpack` FROM `Default_LOADOUT` WHERE `InstanceID` = %d", serverId );

	Sqf::Value inventory = lexical_cast<Sqf::Value>("[]");
	Sqf::Value backpack = lexical_cast<Sqf::Value>("[]");

	if (defLoadoutRes && defLoadoutRes->fetchRow())
	{
		if (!defLoadoutRes->at(0).isNull())
		{
			try
			{
				inventory = lexical_cast<Sqf::Value>(defLoadoutRes->at(0).getString());
			}
			catch (bad_lexical_cast)
			{
				_logger.warning("Invalid default inventory for InstanceID("+lexical_cast<string>(serverId)+"): "+defLoadoutRes->at(0).getString());
			}
		}
		if (!defLoadoutRes->at(1).isNull())
		{
			try
			{
				backpack = lexical_cast<Sqf::Value>(defLoadoutRes->at(1).getString());
			}
			catch (bad_lexical_cast)
			{
				_logger.warning("Invalid default backpack for InstanceID("+lexical_cast<string>(serverId)+"): "+defLoadoutRes->at(1).getString());
			}
		}
		retVal.push_back(string("PASS"));
		retVal.push_back(inventory);
		retVal.push_back(backpack);
	}
	else
	{
		retVal.push_back(string("ERROR"));
	}

	return retVal;
}
