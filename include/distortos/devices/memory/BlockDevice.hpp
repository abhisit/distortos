/**
 * \file
 * \brief BlockDevice class header
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_MEMORY_BLOCKDEVICE_HPP_
#define INCLUDE_DISTORTOS_DEVICES_MEMORY_BLOCKDEVICE_HPP_

#include <cstddef>
#include <cstdint>

namespace distortos
{

namespace devices
{

/**
 * BlockDevice class is an interface for a block device.
 *
 * \ingroup devices
 */

class BlockDevice
{
public:

	/**
	 * \brief BlockDevice's destructor
	 */

	virtual ~BlockDevice() = default;

	/**
	 * \brief Closes device.
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is already completely closed;
	 */

	virtual int close() = 0;

	/**
	 * \brief Erases blocks on a device.
	 *
	 * \param [in] address is the address of range that will be erased, must be a multiple of block size
	 * \param [in] size is the size of erased range, bytes, must be a multiple of block size
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 * - EINVAL - \a address and/or \a size are not valid;
	 * - ENOSPC - selected range is greater than size of device;
	 */

	virtual int erase(uint64_t address, uint64_t size) = 0;

	/**
	 * \return block size, bytes
	 */

	virtual size_t getBlockSize() const = 0;

	/**
	 * \return size of block device, bytes
	 */

	virtual uint64_t getSize() const = 0;

	/**
	 * \brief Locks the device for exclusive use by current thread.
	 *
	 * When the object is locked, any call to any member function from other thread will be blocked until the object is
	 * unlocked. Locking is optional, but may be useful when more than one transaction must be done atomically.
	 *
	 * \note Locks are recursive.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \return 0 on success, error code otherwise:
	 * - EAGAIN - the lock could not be acquired because the maximum number of recursive locks for device has been
	 * exceeded;
	 */

	virtual int lock() = 0;

	/**
	 * \brief Opens device.
	 *
	 * \return 0 on success, error code otherwise:
	 * - EMFILE - this device is already opened too many times;
	 */

	virtual int open() = 0;

	/**
	 * \brief Reads data from a device.
	 *
	 * \param [in] address is the address of data that will be read, must be a multiple of block size
	 * \param [out] buffer is the buffer into which the data will be read
	 * \param [in] size is the size of \a buffer, bytes, must be a multiple of block size
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 * - EINVAL - \a address and/or \a buffer and/or \a size are not valid;
	 * - ENOSPC - selected range is greater than size of device;
	 */

	virtual int read(uint64_t address, void* buffer, size_t size) = 0;

	/**
	 * \brief Synchronizes state of a device, ensuring all cached writes are finished.
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 */

	virtual int synchronize() = 0;

	/**
	 * \brief Unlocks the device which was previously locked by current thread.
	 *
	 * \note Locks are recursive.
	 *
	 * \warning This function must not be called from interrupt context!
	 *
	 * \return 0 on success, error code otherwise:
	 * - EPERM - current thread did not lock the device;
	 */

	virtual int unlock() = 0;

	/**
	 * \brief Writes data to a device.
	 *
	 * \param [in] address is the address of data that will be written, must be a multiple of block size
	 * \param [in] buffer is the buffer with data that will be written
	 * \param [in] size is the size of \a buffer, bytes, must be a multiple of block size
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the device is not opened;
	 * - EINVAL - \a address and/or \a buffer and/or \a size are not valid;
	 * - ENOSPC - selected range is greater than size of device;
	 */

	virtual int write(uint64_t address, const void* buffer, size_t size) = 0;

	BlockDevice() = default;
	BlockDevice(const BlockDevice&) = delete;
	BlockDevice& operator=(const BlockDevice&) = delete;
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_MEMORY_BLOCKDEVICE_HPP_
