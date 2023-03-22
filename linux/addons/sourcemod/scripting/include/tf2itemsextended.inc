/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod (C)2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This file is part of the SourceMod/SourcePawn SDK.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#if defined _tf2items_extended_stocks
 #endinput
#endif
#define _tf2items_extended_stocks

#include <tf2itemsinfo>

/**
 * Finds an attribute and its index within a TF2Items item handle.
 *
 * @param hItem			Handle to the TF2Items object that we'll be operating with.
 * @param iAttribute	Item attribute to find.
 * @return				Attribute index if found, -1 otherwise.
 */
stock TF2Items_FindAttributeIndex(Handle:hItem, iAttribute)
{
	new iNumAttributes = TF2Items_GetNumAttributes(hItem);
	for(new i = 0; i < iNumAttributes; i++)
	{
		if(TF2Items_GetAttributeId(hItem, i) == iAttribute)
			return i;
	}
	return -1;
}

/**
 * Replaces (or inserts) an attribute within a TF2Items item handle.
 *
 * @param hItem			Handle to the TF2Items object that we'll be operating with.
 * @param iAttribute	Item attribute replace/insert.
 * @param flValue		Value of the attribute.
 * @param bForce		Insert a new attribute if attribute can't be replaced?.
 * @return				True if replaced or inserted, false otherwise.
 */
stock TF2Items_ReplaceAttribute(Handle:hItem, iAttribute, Float:flValue, bool:bInsert = true)
{
	new iNumAttributes = TF2Items_GetNumAttributes(hItem);
	for(new i = 0; i < iNumAttributes; i++)
	{
		if(TF2Items_GetAttributeId(hItem, i) == iAttribute)
		{
			TF2Items_SetAttribute(hItem, i, iAttribute, flValue);
			return true;
		}
	}

	if(bInsert && iNumAttributes + 1 <= 15)
	{
		TF2Items_SetNumAttributes(hItem, iNumAttributes + 1);
		TF2Items_SetAttribute(hItem, iNumAttributes, iAttribute, flValue);
		return true;
	}

	return false;
}

/**
 * Replaces (or inserts) an attribute within a TF2Items item handle.
 *
 * @param hItem			Handle to the TF2Items object that we'll be operating with.
 * @param strAttribute	Name of the attribute to replace/insert.
 * @param flValue			Value of the attribute.
 * @param bForce			Insert a new attribute if attribute can't be replaced?.
 * @return					True if replaced or inserted, false otherwise.
 */
stock TF2Items_ReplaceAttributeByName(Handle:hItem, const String:strAttribute[], Float:flValue, bool:bInsert = true)
{
	new iNumAttributes = TF2Items_GetNumAttributes(hItem);
	decl String:strName[56];
	for(new i = 0; i < iNumAttributes; i++)
	{
		new iAttribute = TF2Items_GetAttributeId(hItem, i);
		TF2II_GetAttributeNameByID(iAttribute, strName, sizeof(strName));
		if(StrEqual(strAttribute, strName))
		{
			TF2Items_SetAttribute(hItem, i, iAttribute, flValue);
			return true;
		}
	}

	if(bInsert && iNumAttributes + 1 <= 15)
	{
		TF2Items_SetNumAttributes(hItem, iNumAttributes + 1);
		TF2Items_SetAttribute(hItem, iNumAttributes, TF2II_GetAttributeIDByName(strAttribute), flValue);
		PrintToServer("%i - %f", TF2II_GetAttributeIDByName(strAttribute), flValue);
		return true;
	}

	return false;
}

/**
 * Adds to an attribute within a TF2Items item handle.
 *
 * @param hItem			Handle to the TF2Items object that we'll be operating with.
 * @param iAttribute		Index of the attribute to add to.
 * @param flValue			How much to add to the attribute value.
 * @return					True if added, false otherwise.
 */
stock bool:TF2Items_AddAttribute(Handle:hItem, iAttribute, Float:flAmount)
{
	for(new i = 0; i < TF2Items_GetNumAttributes(hItem); i++)
	{
		if(TF2Items_GetAttributeId(hItem, i) == iAttribute)
		{
			new Float:flCurrent = TF2Items_GetAttributeValue(hItem, i);
			TF2Items_SetAttribute(hItem, i, iAttribute, flCurrent + flAmount);
			return true;
		}
	}
	return false;
}

/**
 * Adds to an attribute within a TF2Items item handle.
 *
 * @param hItem			Handle to the TF2Items object that we'll be operating with.
 * @param strAttribute	Name of the attribute to add to.
 * @param flValue			How much to add to the attribute value.
 * @return					True if added, false otherwise.
 */
stock bool:TF2Items_AddAttributeByName(Handle:hItem, const String:strAttribute[], Float:flAmount)
{
	decl String:strName[56];
	for(new i = 0; i < TF2Items_GetNumAttributes(hItem); i++)
	{
		TF2II_GetAttribName(TF2Items_GetAttributeId(hItem, i), strName, sizeof(strName));
		if(StrEqual(strAttribute, strName))
		{
			new Float:flCurrent = TF2Items_GetAttributeValue(hItem, i);
			TF2Items_SetAttribute(hItem, i, iAttribute, flCurrent + flAmount);
			return true;
		}
	}
	return false;
}

/**
 * Subtracts from an attribute within a TF2Items item handle.
 *
 * @param hItem			Handle to the TF2Items object that we'll be operating with.
 * @param iAttribute		Index of the attribute to subtract from.
 * @param flValue			How much to subtract from the attribute value.
 * @return					True if subtracted, false otherwise.
 */
stock bool:TF2Items_SubtractAttribute(Handle:hItem, iAttribute, Float:flAmount)
{
	for(new i = 0; i < TF2Items_GetNumAttributes(hItem); i++)
	{
		if(TF2Items_GetAttributeId(hItem, i) == iAttribute)
		{
			new Float:flCurrent = TF2Items_GetAttributeValue(hItem, i);
			TF2Items_SetAttribute(hItem, i, iAttribute, flCurrent - flAmount);
			return true;
		}
	}
	return false;
}

/**
 * Subtracts from an attribute within a TF2Items item handle.
 *
 * @param hItem			Handle to the TF2Items object that we'll be operating with.
 * @param iAttribute		Name of the attribute to subtract from.
 * @param flValue			How much to subtract from the attribute value.
 * @return					True if subtracted, false otherwise.
 */
stock bool:TF2Items_SubtractAttributeByName(Handle:hItem, const String:strAttribute[], Float:flAmount)
{
	decl String:strName[56];
	for(new i = 0; i < TF2Items_GetNumAttributes(hItem); i++)
	{
		TF2II_GetAttribName(TF2Items_GetAttributeId(hItem, i), strName, sizeof(strName));
		if(StrEqual(strAttribute, strName))
		{
			new Float:flCurrent = TF2Items_GetAttributeValue(hItem, i);
			TF2Items_SetAttribute(hItem, i, iAttribute, flCurrent - flAmount);
			return true;
		}
	}
	return false;
}

/**
 * Removes an attribute within a TF2Items item handle.
 *
 * @param hItem			Handle to the TF2Items object that we'll be operating with.
 * @param strAttribute	Name of the attribute to remove.
 * @return					True if removed, false otherwise.
 */
stock TF2Items_RemoveAttributeByName(Handle:hItem, const String:strAttribute[])
{
	decl String:strName[56];
	decl String:strFormat[56];
	for(new i = 0; i < TF2Items_GetNumAttributes(hItem); i++)
	{
		new iAttribute = TF2Items_GetAttributeId(hItem, i);
		TF2II_GetAttribName(iAttribute, strName, sizeof(strName));
		if(StrContains(strName, "eater", false) != -1)
			continue;

		if(StrContains(strAttribute, strName))
		{
			TF2II_GetAttribDescrFormat(iAttribute, strFormat, sizeof(strFormat));
			if(StrContains(strFormat, "percentage", false) != -1)
				TF2Items_ReplaceAttribute(hItem, iAttribute, 1.0);
			else
				TF2Items_ReplaceAttribute(hItem, iAttribute, 0.0);

			return true;
		}
	}

	return false;
}

/**
 * Removes all default attributes within a TF2Items item handle,
 * (default attributes found from items_game.txt).
 *
 * @param hItem			Handle to the TF2Items object that we'll be operating with.
 * @noreturn
 */
stock TF2Items_RemoveDefaultAttributes(Handle:hItem)
{
	decl String:strName[56];
	decl String:strFormat[56];

	for(new i = 0; i < TF2Items_GetNumAttributes(hItem); i++)
	{
		new iAttribute = TF2Items_GetAttributeId(hItem, i);
		TF2II_GetAttribName(iAttribute, strName, sizeof(strName));
		if(StrContains(strName, "eater", false) != -1)
			continue;

		TF2II_GetAttribDescrFormat(iAttribute, strFormat, sizeof(strFormat));
		if(StrContains(strFormat, "percentage", false) != -1)
			TF2Items_ReplaceAttribute(hItem, iAttribute, 1.0);
		else
			TF2Items_ReplaceAttribute(hItem, iAttribute, 0.0);
	}
}