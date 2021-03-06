#include <sys/types.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

#include <linux/if_ether.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#include <libubus.h>
#include <libubox/blobmsg.h>
#include <libubox/uloop.h>
#include <libubox/ulog.h>
#include <libubox/avl.h>
#include <libubox/avl-cmp.h>

#define EIR_FLAGS			0x01
#define EIR_UUID16_SOME			0x02
#define EIR_UUID16_ALL			0x03
#define EIR_UUID32_SOME			0x04
#define EIR_UUID32_ALL			0x05
#define EIR_UUID128_SOME		0x06
#define EIR_UUID128_ALL			0x07
#define EIR_NAME_SHORT			0x08
#define EIR_NAME_COMPLETE		0x09
#define EIR_TX_POWER			0x0A
#define EIR_DEVICE_ID			0x10
#define EIR_MANUFACTURE_SPECIFIC	0xFF

struct btle_config {
	int lescan_timeout;
	int lescan_max_age;
	int _6lowpan;
};

struct btle_peer {
	struct avl_node avl;

	char name[256];
	char addr[ETH_ALEN * 3];
	int8_t rssi;
	int public;
	uint8_t flags;
	uint16_t handle;
	struct timespec ts;
	int conn;
	int conn_handle;
	int conn_state;
	int conn_type;

	char uuid16[5];
	char uuid128[33];
};

extern struct uloop_fd fd;
extern struct btle_config config;
extern struct avl_tree peer_tree;
extern int hdev;

void btle_6lowpan_init(void);
void btle_6lowpan_connect(struct btle_peer *peer);
void btle_6lowpan_disconnect(struct btle_peer *peer);

void ubus_init(void);

