//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
message BTSPD_NewAddrFound
{
    @omitGetVerb(true);
    string addr;
    string port;
}

// announce event types
enum ATTACK_TYPE
{
    ADDR_FOUND_ACTIVE_CONN = 1; // address found using active conn
    ADDR_FOUND_PASSIVE_CONN = 2; // address found using passive conn
}

packet BTSPDAttackMessage
{
    @omitGetVerb(true);
    string attacker;
    string victim;
    string attackerAddr;
    
    unsigned int attackType @enum(ATTACK_TYPE);
    
}
    

