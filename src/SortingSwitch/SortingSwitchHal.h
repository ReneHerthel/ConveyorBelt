/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

 /**
  * @ingroup    sorting_switch
  * @{
  *
  * @brief      Header of the SortingSwitch component
  *
  * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
  */

#ifndef SORTINGSWITCH_H_
#define SORTINGSWITCH_H_

#include "BSortingSwitch.h"

class SortingSwitchHal : public BSortingSwitch {
public:
	/*
	 * @brief Default constructor.
	 */
	SortingSwitchHal();
	~SortingSwitchHal();
	void open();
	void close();
};

#endif /* SORTINGSWITCH_H_ */
/** @} */
