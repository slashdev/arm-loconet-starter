/**
 * @file loconet.c
 * @brief Loconet base functionality
 *
 * \copyright Copyright 2017 /Dev. All rights reserved.
 * \license This project is released under MIT license.
 *
 * @author Ferdi van der Werf <ferdi@slashdev.nl>
 */
#include "loconet.h"

// Define LOCONET_RX_RINGBUFFER_Size if it's not defined
#ifndef LOCONET_RX_RINGBUFFER_Size
#define LOCONET_RX_RINGBUFFER_Size 64
#endif

typedef struct {
  uint8_t buffer[LOCONET_RX_RINGBUFFER_Size];
  volatile uint8_t writer;
  volatile uint8_t reader;
} LOCONET_RX_RINGBUFFER_Type;

static LOCONET_RX_RINGBUFFER_Type loconet_rx_ringbuffer = { { 0 }, 0, 0};

void loconet_rx_ringbuffer_push(uint8_t byte)
{
  // Get index + 1 of buffer head
  uint8_t index = (loconet_rx_ringbuffer.writer + 1) % LOCONET_RX_RINGBUFFER_Size;

  // If the buffer is full, wait until the reader empties
  // a slot in the buffer to write to.
  while (index == loconet_rx_ringbuffer.reader) {
    continue;
  }

  // Write the byte
  loconet_rx_ringbuffer.buffer[loconet_rx_ringbuffer.writer] = byte;
  loconet_rx_ringbuffer.writer = index;
}
