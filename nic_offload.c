/*
 * Print NIC's offload capability
 *
 */
#ifndef __NIC_OFFLOAD_C__
#define __NIC_OFFLOAD_C__

#include <rte_common.h>
#include <rte_ether.h>
#include <rte_ethdev.h>

struct nic_ol_capa 
{
    uint32_t value;
    char    *desc;
};

static struct nic_ol_capa rx_offload_list[] = {
    { DEV_RX_OFFLOAD_VLAN_STRIP,        "VLAN strip" },
    { DEV_RX_OFFLOAD_IPV4_CKSUM,        "IPv4 checksum" },
    { DEV_RX_OFFLOAD_UDP_CKSUM,         "UDP checksum" },
    { DEV_RX_OFFLOAD_TCP_CKSUM,         "TCP checksum" },
    { DEV_RX_OFFLOAD_TCP_LRO,           "TCP LRO" },
    { DEV_RX_OFFLOAD_QINQ_STRIP,        "QinQ strip" },
};

static struct nic_ol_capa tx_offload_list[] = {
    { DEV_TX_OFFLOAD_VLAN_INSERT,       "VLAN insert" },
    { DEV_TX_OFFLOAD_IPV4_CKSUM,        "IPv4 checksum" },
    { DEV_TX_OFFLOAD_UDP_CKSUM,         "UDP checksum" },
    { DEV_TX_OFFLOAD_TCP_CKSUM,         "TCP checksum" },
    { DEV_TX_OFFLOAD_SCTP_CKSUM,        "SCTP checksum" },
    { DEV_TX_OFFLOAD_TCP_TSO,           "TCP TSO" },
    { DEV_TX_OFFLOAD_UDP_TSO,           "UDP TSO" },
    { DEV_TX_OFFLOAD_OUTER_IPV4_CKSUM,  "Outer IPv4 checksum" },
    { DEV_TX_OFFLOAD_QINQ_INSERT,       "IPv4 checksum" },
};

void dump_pmd_offload(uint32_t nb_port);
static void print_pmd_offload(uint32_t nic_ol, struct nic_ol_capa ol_list[]);


/**
 * Print the meaning of NIC offload capability
 * 
 * @param nic_ol : NIC's offload capability
 * @param offload_list : DPDK supported offload feature list
 */
static void print_pmd_offload(uint32_t nic_ol, struct nic_ol_capa ol_list[])
{
    uint32_t i;
    uint32_t nb_ol;

    nb_ol = sizeof(ol_list)/sizeof(ol_list[0]);

    for (i = 0; i < nb_ol; i++)
    {
        printf("%30s : %s\n"
                , ol_list[i].desc
                , ((ol_list[i].value & nic_ol) == 1) ? "Enabled" 
                                                     : "Disabled");
    }
}

/**
 * 
 */
void dump_pmd_offload(uint32_t nb_port)
{
    uint32_t port_id;
    struct rte_eth_dev_info dev_info;

    for (port_id = 0; port_id < nb_port; port_id++) 
    {
        rte_eth_dev_info_get(port_id, &dev_info);

        printf("Rx offload : 0x%08x\n", dev_info.rx_offload_capa);
        if (dev_info.rx_offload_capa != 0)
            print_pmd_offload(dev_info.rx_offload_capa, rx_offload_list);

        printf("Tx offload : 0x%08x\n", dev_info.tx_offload_capa);
        if (dev_info.tx_offload_capa != 0)
            print_pmd_offload(dev_info.tx_offload_capa, tx_offload_list);
    }
}

#endif /* __NIC_OFFLOAD_C__ */
