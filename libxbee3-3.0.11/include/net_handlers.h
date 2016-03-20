#ifndef __XBEE_NET_HANDLERS_H
#define __XBEE_NET_HANDLERS_H

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

#ifndef XBEE_NO_NET_SERVER

xbee_err xbee_netServer_fc_rx_func(struct xbee *xbee, void *arg, unsigned char identifier, struct xbee_tbuf *buf, struct xbee_frameInfo *frameInfo, struct xbee_conAddress *address, struct xbee_pkt **pkt);
xbee_err xbee_netServer_fc_tx_func(struct xbee *xbee, struct xbee_con *con, void *arg, unsigned char identifier, unsigned char frameId, struct xbee_conAddress *address, struct xbee_conSettings *settings, const unsigned char *buf, int len, struct xbee_sbuf **oBuf);

extern const struct xbee_mode xbee_netServerMode;

#endif /* XBEE_NO_NET_SERVER */

extern struct xbee_modeDataHandlerRx xbee_netServer_backchannel_rx;
extern struct xbee_modeDataHandlerTx xbee_netServer_backchannel_tx;

#endif /* __XBEE_NET_HANDLERS_H */
