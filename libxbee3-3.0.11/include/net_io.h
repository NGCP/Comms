#ifndef __XBEE_NET_IO_H
#define __XBEE_NET_IO_H

/*
	libxbee - a C/C++ library to aid the use of Digi's XBee wireless modules
	          running in API mode.

	Copyright (C) 2009 onwards  Attie Grande (attie@attie.co.uk)

	libxbee is free software: you can redistribute it and/or modify it
	under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	libxbee is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

xbee_err xbee_netRx(struct xbee *xbee, void *arg, struct xbee_tbuf **buf);
xbee_err xbee_netTx(struct xbee *xbee, void *arg, struct xbee_sbuf *buf);

#endif /* __XBEE_NET_IO_H */
