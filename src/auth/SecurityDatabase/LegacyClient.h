/*
 *	PROGRAM:		Firebird authentication
 *	MODULE:			LegacyClient.h
 *	DESCRIPTION:	Performs legacy actions on DPB at client side.
 *
 *  The contents of this file are subject to the Initial
 *  Developer's Public License Version 1.0 (the "License");
 *  you may not use this file except in compliance with the
 *  License. You may obtain a copy of the License at
 *  http://www.ibphoenix.com/main.nfs?a=ibphoenix&page=ibp_idpl.
 *
 *  Software distributed under the License is distributed AS IS,
 *  WITHOUT WARRANTY OF ANY KIND, either express or implied.
 *  See the License for the specific language governing rights
 *  and limitations under the License.
 *
 *  The Original Code was created by Alex Peshkov
 *  for the Firebird Open Source RDBMS project.
 *
 *  Copyright (c) 2010 Alex Peshkov <peshkoff at mail.ru>
 *  and all contributors signed below.
 *
 *  All Rights Reserved.
 *  Contributor(s): ______________________________________.
 */

#ifndef AUTH_LEGACY_CLIENT_H
#define AUTH_LEGACY_CLIENT_H

#include "../auth/AuthInterface.h"
#include "../common/classes/ImplementHelper.h"

namespace Auth {

// Required to stop analyzing rest of plugins before first roundtrip to server
// if legacy login is present in DPB

class SecurityDatabaseClient : public Firebird::StdPlugin<IClient, FB_AUTH_CLIENT_VERSION>
{
public:
	explicit SecurityDatabaseClient(Firebird::IPluginConfig*)
	{
	}

	// IClient implementation
	Result FB_CARG startAuthentication(Firebird::IStatus* status, const AuthTags* tags, IClumplets* dpb);
	Result FB_CARG contAuthentication(Firebird::IStatus* status, const unsigned char* data, unsigned int size);
    void FB_CARG getData(const unsigned char** data, unsigned short* dataSize);
    int FB_CARG release();
};

void registerLegacyClient(Firebird::IPluginManager* iPlugin);

} // namespace Auth

#endif // AUTH_LEGACY_CLIENT_H