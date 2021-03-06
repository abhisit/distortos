/**
 * \file
 * \brief MutexRecursiveOperationsTestCase class header
 *
 * \author Copyright (C) 2014-2017 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef TEST_MUTEX_MUTEXRECURSIVEOPERATIONSTESTCASE_HPP_
#define TEST_MUTEX_MUTEXRECURSIVEOPERATIONSTESTCASE_HPP_

#include "PrioritizedTestCase.hpp"

namespace distortos
{

namespace test
{

/**
 * \brief Tests operations in scenarios specific for recursive type of mutex.
 *
 * Tests locking (lock(), tryLock(), tryLockFor() and tryLockUntil()) and unlocking.
 */

class MutexRecursiveOperationsTestCase : public PrioritizedTestCase
{
	/// priority at which this test case should be executed
	constexpr static uint8_t testCasePriority_ {UINT8_MAX - 1};

public:

	/**
	 * \brief MutexRecursiveOperationsTestCase's constructor
	 */

	constexpr MutexRecursiveOperationsTestCase() :
			PrioritizedTestCase{testCasePriority_}
	{

	}

private:

	/**
	 * \brief Runs the test case.
	 *
	 * \return true if the test case succeeded, false otherwise
	 */

	bool run_() const override;
};

}	// namespace test

}	// namespace distortos

#endif	// TEST_MUTEX_MUTEXRECURSIVEOPERATIONSTESTCASE_HPP_
