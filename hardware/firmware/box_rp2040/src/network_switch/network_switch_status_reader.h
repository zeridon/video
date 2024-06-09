#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t bmcr;  // Basic mode control register
    uint32_t bmsr;  // Basic mode status register
    uint32_t an;    // Auto negotiation settings
    uint32_t lpa ;  // Link partner ability
    uint32_t gbec;
    uint32_t gbes;
} nsw_port_regs_t;

typedef enum {
    nsw_link_unknown,
    nsw_link_down,
    nsw_link_full_duplex,
    nsw_link_half_duplex
} nsw_link_state_t;

void nsw_init(void);
bool nsw_identify(uint32_t* id, uint32_t* ver);
bool nsw_read_port_regs(uint8_t port, nsw_port_regs_t* regs);
nsw_link_state_t nsw_link_state(nsw_port_regs_t* regs);
uint16_t nsw_link_speed_mbps(nsw_port_regs_t* regs);
