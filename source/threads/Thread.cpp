/**
 * \file
 * \brief Thread class implementation
 *
 * \author Copyright (C) 2014-2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-11-13
 */

#include "distortos/Thread.hpp"

#include "distortos/scheduler/getScheduler.hpp"
#include "distortos/scheduler/Scheduler.hpp"

namespace distortos
{

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

Thread::~Thread()
{

}

/*---------------------------------------------------------------------------------------------------------------------+
| protected static functions
+---------------------------------------------------------------------------------------------------------------------*/

void Thread::threadRunner(Thread& thread)
{
	thread.run();
	scheduler::getScheduler().remove(&Thread::terminationHook);

	while (1);
}

}	// namespace distortos