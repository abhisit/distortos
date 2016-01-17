/**
 * \file
 * \brief Header for RCC-related functions for STM32F4
 *
 * This file covers devices as described in following places:
 * - RM0368 reference manual (STM32F401xB/C and STM32F401xD/E), Revision 4, 2015-05-04
 * - RM0090 reference manual (STM32F405/415, STM32F407/417, STM32F427/437 and STM32F429/439), Revision 11, 2015-10-20
 * - RM0401 reference manual (STM32F410), Revision 2, 2015-10-26
 * - RM0383 reference manual (STM32F411xC/E), Revision 1, 2014-07-24
 * - RM0390 reference manual (STM32F446xx), Revision 1, 2015-03-17
 * - RM0386 reference manual (STM32F469xx and STM32F479xx), Revision 2, 2015-11-19
 *
 * \author Copyright (C) 2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_STM32F4_INCLUDE_DISTORTOS_CHIP_STM32F4_RCC_HPP_
#define SOURCE_CHIP_STM32_STM32F4_INCLUDE_DISTORTOS_CHIP_STM32F4_RCC_HPP_

#include "distortos/distortosConfiguration.h"

#include <array>

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| global types
+---------------------------------------------------------------------------------------------------------------------*/

/// system clock source
enum class SystemClockSource : uint8_t
{
	/// HSI oscillator selected as system clock
	hsi,
	/// HSE oscillator selected as system clock
	hse,
	/// main PLL selected as system clock
	pll,

#if defined(CONFIG_CHIP_STM32F446) || defined(CONFIG_CHIP_STM32F469) || defined(CONFIG_CHIP_STM32F479)

	/// main PLL's "/R" output selected as system clock
	pllr,

#endif	// defined(CONFIG_CHIP_STM32F446) || defined(CONFIG_CHIP_STM32F469) || defined(CONFIG_CHIP_STM32F479)
};

/*---------------------------------------------------------------------------------------------------------------------+
| global constants
+---------------------------------------------------------------------------------------------------------------------*/

/// minimum allowed value for PLLM
constexpr uint8_t minPllm {2};

/// maximum allowed value for PLLM
constexpr uint8_t maxPllm {63};

/// minimum allowed value for PLLN
#if defined(CONFIG_CHIP_STM32F401) || defined(CONFIG_CHIP_STM32F446)
constexpr uint16_t minPlln {192};
#else	// !defined(CONFIG_CHIP_STM32F401) && !defined(CONFIG_CHIP_STM32F446)
constexpr uint16_t minPlln {50};
#endif	// !defined(CONFIG_CHIP_STM32F401) && !defined(CONFIG_CHIP_STM32F446)

/// maximum allowed value for PLLN
constexpr uint16_t maxPlln {432};

/// minimum allowed value for PLLQ
constexpr uint8_t minPllq {2};

/// maximum allowed value for PLLQ
constexpr uint8_t maxPllq {15};

#if defined(CONFIG_CHIP_STM32F446) || defined(CONFIG_CHIP_STM32F469) || defined(CONFIG_CHIP_STM32F479)

/// minimum allowed value for PLLR
constexpr uint8_t minPllr {2};

/// maximum allowed value for PLLR
constexpr uint8_t maxPllr {7};

#endif	// defined(CONFIG_CHIP_STM32F446) || defined(CONFIG_CHIP_STM32F469) || defined(CONFIG_CHIP_STM32F479)

/// first allowed value for PLLP - 2
constexpr uint8_t pllpDiv2 {2};

/// second allowed value for PLLP - 4
constexpr uint8_t pllpDiv4 {4};

/// third allowed value for PLLP - 6
constexpr uint8_t pllpDiv6 {6};

/// fourth allowed value for PLLP - 8
constexpr uint8_t pllpDiv8 {8};

/// HSI clock frequency, Hz
constexpr uint32_t hsiHz {16000000};

/// minimum allowed value for VCO input frequency, Hz
constexpr uint32_t minVcoInHz {1000000};

/// maximum allowed value for VCO input frequency, Hz
constexpr uint32_t maxVcoInHz {2000000};

/// minimum allowed value for VCO output frequency, Hz
#if defined(CONFIG_CHIP_STM32F401)
constexpr uint32_t minVcoOutHz {192000000};
#else	// !defined(CONFIG_CHIP_STM32F401)
constexpr uint32_t minVcoOutHz {100000000};
#endif	// !defined(CONFIG_CHIP_STM32F401)

/// maximum allowed value for VCO output frequency, Hz
constexpr uint32_t maxVcoOutHz {432000000};

/// maximum allowed value for PLL output frequency, Hz
/// [0] - in overdrive mode with voltage scale 1
/// [1] - with voltage scale 1
/// [2] - with voltage scale 2
/// [3] - with voltage scale 3
#if defined(CONFIG_CHIP_STM32F401)
constexpr std::array<uint32_t, 4> maxPllOutHz {0, 0, 84000000, 60000000};
#elif defined(CONFIG_CHIP_STM32F405) || defined(CONFIG_CHIP_STM32F407) || defined(CONFIG_CHIP_STM32F415) || \
		defined(CONFIG_CHIP_STM32F417)
constexpr std::array<uint32_t, 4> maxPllOutHz {0, 168000000, 144000000, 0};
#elif defined(CONFIG_CHIP_STM32F410) || defined(CONFIG_CHIP_STM32F411)
constexpr std::array<uint32_t, 4> maxPllOutHz {0, 100000000, 84000000, 64000000};
#else	// !defined(CONFIG_CHIP_STM32F401) && !defined(CONFIG_CHIP_STM32F405) && !defined(CONFIG_CHIP_STM32F407) &&
		// !defined(CONFIG_CHIP_STM32F415) && !defined(CONFIG_CHIP_STM32F417) && !defined(CONFIG_CHIP_STM32F410) &&
		// !defined(CONFIG_CHIP_STM32F411)
constexpr std::array<uint32_t, 4> maxPllOutHz {180000000, 168000000, 144000000, 120000000};
#endif	// !defined(CONFIG_CHIP_STM32F401) && !defined(CONFIG_CHIP_STM32F405) && !defined(CONFIG_CHIP_STM32F407) &&
		// !defined(CONFIG_CHIP_STM32F415) && !defined(CONFIG_CHIP_STM32F417) && !defined(CONFIG_CHIP_STM32F410) &&
		// !defined(CONFIG_CHIP_STM32F411)

/// maximum allowed value for PLL "Q" output frequency, Hz
constexpr uint32_t maxPllqOutHz {48000000};

/// maximum allowed APB1 (low speed) frequency, Hz
#if defined(CONFIG_CHIP_STM32F401) || defined(CONFIG_CHIP_STM32F405) || defined(CONFIG_CHIP_STM32F407) || \
		defined(CONFIG_CHIP_STM32F415) || defined(CONFIG_CHIP_STM32F417)
constexpr uint32_t maxApb1Hz {42000000};
#elif defined(CONFIG_CHIP_STM32F410) || defined(CONFIG_CHIP_STM32F411)
constexpr uint32_t maxApb1Hz {50000000};
#else	// !defined(CONFIG_CHIP_STM32F401) && !defined(CONFIG_CHIP_STM32F405) && !defined(CONFIG_CHIP_STM32F407) &&
		// !defined(CONFIG_CHIP_STM32F415) && !defined(CONFIG_CHIP_STM32F417) && !defined(CONFIG_CHIP_STM32F410) &&
		// !defined(CONFIG_CHIP_STM32F411)
constexpr uint32_t maxApb1Hz {45000000};
#endif	// !defined(CONFIG_CHIP_STM32F401) && !defined(CONFIG_CHIP_STM32F405) && !defined(CONFIG_CHIP_STM32F407) &&
		// !defined(CONFIG_CHIP_STM32F415) && !defined(CONFIG_CHIP_STM32F417) && !defined(CONFIG_CHIP_STM32F410) &&
		// !defined(CONFIG_CHIP_STM32F411)

/// maximum allowed APB2 (high speed) frequency, Hz
#if defined(CONFIG_CHIP_STM32F401) || defined(CONFIG_CHIP_STM32F405) || defined(CONFIG_CHIP_STM32F407) || \
		defined(CONFIG_CHIP_STM32F415) || defined(CONFIG_CHIP_STM32F417)
constexpr uint32_t maxApb2Hz {84000000};
#elif defined(CONFIG_CHIP_STM32F410) || defined(CONFIG_CHIP_STM32F411)
constexpr uint32_t maxApb2Hz {100000000};
#else	// !defined(CONFIG_CHIP_STM32F401) && !defined(CONFIG_CHIP_STM32F405) && !defined(CONFIG_CHIP_STM32F407) &&
		// !defined(CONFIG_CHIP_STM32F415) && !defined(CONFIG_CHIP_STM32F417) && !defined(CONFIG_CHIP_STM32F410) &&
		// !defined(CONFIG_CHIP_STM32F411)
constexpr uint32_t maxApb2Hz {90000000};
#endif	// !defined(CONFIG_CHIP_STM32F401) && !defined(CONFIG_CHIP_STM32F405) && !defined(CONFIG_CHIP_STM32F407) &&
		// !defined(CONFIG_CHIP_STM32F415) && !defined(CONFIG_CHIP_STM32F417) && !defined(CONFIG_CHIP_STM32F410) &&
		// !defined(CONFIG_CHIP_STM32F411)

/// first allowed value for AHB divider - 1
constexpr uint16_t hpreDiv1 {1};

/// second allowed value for AHB divider - 2
constexpr uint16_t hpreDiv2 {2};

/// third allowed value for AHB divider - 4
constexpr uint16_t hpreDiv4 {4};

/// fourth allowed value for AHB divider - 8
constexpr uint16_t hpreDiv8 {8};

/// fifth allowed value for AHB divider - 16
constexpr uint16_t hpreDiv16 {16};

/// sixth allowed value for AHB divider - 64
constexpr uint16_t hpreDiv64 {64};

/// seventh allowed value for AHB divider - 128
constexpr uint16_t hpreDiv128 {128};

/// eighth allowed value for AHB divider - 256
constexpr uint16_t hpreDiv256 {256};

/// ninth allowed value for AHB divider - 512
constexpr uint16_t hpreDiv512 {512};

/// first allowed value for APB1 and APB2 dividers - 1
constexpr uint8_t ppreDiv1 {1};

/// second allowed value for APB1 and APB2 dividers - 2
constexpr uint8_t ppreDiv2 {2};

/// third allowed value for APB1 and APB2 dividers - 4
constexpr uint8_t ppreDiv4 {4};

/// fourth allowed value for APB1 and APB2 dividers - 8
constexpr uint8_t ppreDiv8 {8};

/// fifth allowed value for APB1 and APB2 dividers - 16
constexpr uint8_t ppreDiv16 {16};

/*---------------------------------------------------------------------------------------------------------------------+
| global functions' declarations
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Configures divider of AHB clock (HPRE value).
 *
 * \param [in] hpre is the HPRE value, {1, 2, 4, 8, 16, 64, 128, 256, 512} or {hpreDiv1, hpreDiv2, hpreDiv4, hpreDiv8,
 * hpreDiv16, hpreDiv64, hpreDiv128, hpreDiv256, hpreDiv512}
 *
 * \return 0 on success, error code otherwise:
 * - EINVAL - \a hpre value is invalid;
 */

int configureAhbClockDivider(uint16_t hpre);

/**
 * \brief Configures divider of APB1 or APB2 clock (PPRE1 or PPRE2 value).
 *
 * \param [in] ppre2 selects whether PPRE1 (false) or PPRE2 (true) is configured
 * \param [in] ppre is the PPRE value, {1, 2, 4, 8, 16} or {ppreDiv1, ppreDiv2, ppreDiv4, ppreDiv8, ppreDiv16}
 *
 * \return 0 on success, error code otherwise:
 * - EINVAL - \a ppre value is invalid;
 */

int configureApbClockDivider(bool ppre2, uint8_t ppre);

/**
 * \brief Configures clock source of main and audio PLLs.
 *
 * \warning Before changing configuration of any PLL make sure that they are not used in any way (as core clock or as
 * source of peripheral clocks) and that they are disabled.
 *
 * \param [in] hse selects whether HSI (false) or HSE (true) is used as clock source of main and audio PLLs
 */

void configurePllClockSource(bool hse);

/**
 * \brief Configures divider of PLL input clock (PLLM value) for main and audio PLLs.
 *
 * \warning Before changing configuration of any PLL make sure that they are not used in any way (as core clock or as
 * source of peripheral clocks) and that they are disabled.
 *
 * \param [in] pllm is the PLLM value for main PLL and audio PLLI2S, [2; 63] or [minPllm; maxPllm]
 *
 * \return 0 on success, error code otherwise:
 * - EINVAL - \a pllm value is invalid;
 */

int configurePllInputClockDivider(uint8_t pllm);

/**
 * \brief Enables HSE clock.
 *
 * Enables HSE clock using crystal/ceramic resonator (bypass disabled) or external user clock (bypass enabled). This
 * function waits until the HSE oscillator is stable after enabling the clock.
 *
 * \warning Before changing configuration of HSE clock make sure that it is not used in any way (as core clock, as
 * source for any PLL or as source of RTC clock).
 *
 * \param [in] bypass selects whether crystal/ceramic resonator (false) or external user clock (true) is used
 */

void enableHse(bool bypass);

#if defined(CONFIG_CHIP_STM32F446) || defined(CONFIG_CHIP_STM32F469) || defined(CONFIG_CHIP_STM32F479)

/**
 * \brief Enables main PLL.
 *
 * Enables main PLL using selected parameters and waits until it is stable.
 *
 * \warning Before changing configuration of main PLL make sure that it is not used in any way (as core clock or as
 * source of peripheral clocks) and that it is disabled.
 *
 * \param [in] plln is the PLLN value for main PLL, [minPlln; maxPlln]
 * \param [in] pllp is the PLLP value for main PLL, {2, 4, 6, 8} or {pllpDiv2, pllpDiv4, pllpDiv6, pllpDiv8}
 * \param [in] pllq is the PLLQ value for main PLL, [2; 15] or [minPllq; maxPllq]
 * \param [in] pllr is the PLLR value for main PLL, [2; 7] or [minPllr; maxPllr]
 *
 * \return 0 on success, error code otherwise:
 * - EINVAL - \a plln or \a pllp or \a pllq or \a pllr value is invalid;
 */

int enablePll(uint16_t plln, uint8_t pllp, uint8_t pllq, uint8_t pllr);

#else	// !defined(CONFIG_CHIP_STM32F446) && !defined(CONFIG_CHIP_STM32F469) && !defined(CONFIG_CHIP_STM32F479)

/**
 * \brief Enables main PLL.
 *
 * Enables main PLL using selected parameters and waits until it is stable.
 *
 * \warning Before changing configuration of main PLL make sure that it is not used in any way (as core clock or as
 * source of peripheral clocks) and that it is disabled.
 *
 * \param [in] plln is the PLLN value for main PLL, [minPlln; maxPlln]
 * \param [in] pllp is the PLLP value for main PLL, {2, 4, 6, 8} or {pllpDiv2, pllpDiv4, pllpDiv6, pllpDiv8}
 * \param [in] pllq is the PLLQ value for main PLL, [2; 15] or [minPllq; maxPllq]
 *
 * \return 0 on success, error code otherwise:
 * - EINVAL - \a plln or \a pllp or \a pllq value is invalid;
 */

int enablePll(uint16_t plln, uint8_t pllp, uint8_t pllq);

#endif	// !defined(CONFIG_CHIP_STM32F446) && !defined(CONFIG_CHIP_STM32F469) && !defined(CONFIG_CHIP_STM32F479)

/**
 * \brief Disables HSE clock.
 *
 * \warning Before changing configuration of HSE clock make sure that it is not used in any way (as core clock, as
 * source for any PLL or as source of RTC clock).
 */

void disableHse();

/**
 * \brief Disables main PLL.
 *
 * \warning Before changing configuration of main PLL make sure that it is not used in any way (as core clock or as
 * source of peripheral clocks).
 */

void disablePll();

#if defined(CONFIG_CHIP_STM32F446) || defined(CONFIG_CHIP_STM32F469) || defined(CONFIG_CHIP_STM32F479)

/**
 * \brief Switches system clock.
 *
 * \param [in] source is the new source of system clock, SystemClockSource::{hsi, hse, pll, pllr}
 */

#else	// !defined(CONFIG_CHIP_STM32F446) && !defined(CONFIG_CHIP_STM32F469) && !defined(CONFIG_CHIP_STM32F479)

/**
 * \brief Switches system clock.
 *
 * \param [in] source is the new source of system clock, SystemClockSource::{hsi, hse, pll}
 */

#endif	// !defined(CONFIG_CHIP_STM32F446) && !defined(CONFIG_CHIP_STM32F469) && !defined(CONFIG_CHIP_STM32F479)

void switchSystemClock(SystemClockSource source);

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_STM32F4_INCLUDE_DISTORTOS_CHIP_STM32F4_RCC_HPP_