#include "ubtle.h"

#define SYSFS_6LOWPAN_ENABLE	"/sys/kernel/debug/bluetooth/6lowpan_enable"
#define SYSFS_6LOWPAN_CONTROL	"/sys/kernel/debug/bluetooth/6lowpan_control"

void btle_6lowpan_init(void)
{
	int fd = open(SYSFS_6LOWPAN_ENABLE, O_WRONLY);

	if (fd < 0) {
		ULOG_ERR("failed to open %s\n", SYSFS_6LOWPAN_ENABLE);
		return;
	}

	if (write(fd, config._6lowpan ? "1" : "0", 1) < 1)
		ULOG_ERR("failed to write %s\n", SYSFS_6LOWPAN_ENABLE);

	close(fd);
}

void btle_6lowpan_connect(struct btle_peer *peer)
{
	int fd = open(SYSFS_6LOWPAN_CONTROL, O_WRONLY);
	char buf[128];
	int len;

	if (fd < 0) {
		ULOG_ERR("failed to open %s\n", SYSFS_6LOWPAN_CONTROL);
		return;
	}

	len = snprintf(buf, sizeof(buf), "connect %s 1", peer->addr);
	if (write(fd, buf, len) < len)
		ULOG_ERR("failed to write %s\n", SYSFS_6LOWPAN_CONTROL);

	close(fd);
}

void btle_6lowpan_disconnect(struct btle_peer *peer)
{
	int fd = open(SYSFS_6LOWPAN_CONTROL, O_WRONLY);
	char buf[128];
	int len;

	if (fd < 0) {
		ULOG_ERR("failed to open %s\n", SYSFS_6LOWPAN_CONTROL);
		return;
	}

	len = snprintf(buf, sizeof(buf), "disconnect %s", peer->addr);
	if (write(fd, buf, len) < len)
		ULOG_ERR("failed to write %s\n", SYSFS_6LOWPAN_CONTROL);

	close(fd);
}
