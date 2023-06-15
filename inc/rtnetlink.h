#ifndef _RTNETLINK_H_
#define _RTNETLINK_H_

#include <stdint.h>
#include <linux/netlink.h>

#define NETLINK_RECEIVE_BUFFER_SIZE 4096
#define NLA_BIN_SIZE(x) (sizeof(struct nlattr) + x)
#define NLA_ATTR(attr) ((void *)attr + NLA_HDRLEN)


/* Netlink attributes */
struct nlattr *set_str8_attr(struct nlattr *, uint16_t, char *);
struct nlattr *set_str_attr(struct nlattr *, uint16_t, char *);
struct nlattr *set_binary_attr(struct nlattr *, uint16_t, uint8_t *, uint64_t);
struct nlattr *set_nested_attr(struct nlattr *, uint16_t, uint16_t);
struct nlattr *set_u32_attr(struct nlattr *, uint16_t, uint32_t);
struct nlattr *set_u16_attr(struct nlattr *, uint16_t, uint16_t);
struct nlattr *set_u8_attr(struct nlattr *, uint16_t, uint8_t);
struct nlattr *set_u64_attr(struct nlattr *, uint16_t, uint64_t);
struct nlattr *set_flag_attr(struct nlattr *, uint16_t);


#endif /* _RTNETLINK_H_ */