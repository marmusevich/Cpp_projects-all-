/*
 *  cApp.h
 *  Kore-Engine
 *
 *  Created by Sean Chapel on 11/15/05.
 *  Copyright 2005 Seoushi Games. All rights reserved.
 *
 */

#include "globals.h"

namespace Kore
{
	class cApp
	{
		public:
				cApp();
				virtual ~cApp();
	
				virtual void Init() = 0;
				virtual void Run() = 0;
				virtual void Shutdown() = 0;
	};
}
