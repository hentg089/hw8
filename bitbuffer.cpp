#include <iostream>
#include <cstring>

#include "bitbuffer.h"


BitBuffer::BitBuffer(const BitBuffer& b) {
  init(b.max_bytes);
  read_head = b.read_head;
  write_head = b.write_head;
  read_offset = b.read_offset;
  write_offset = b.write_offset;  
  memcpy(data,b.data,max_bytes);
}

void BitBuffer::init(size_t nbytes)
{
  data = new byte_t[nbytes];
  max_bytes = nbytes;
  read_head = 0;
  write_head = 0;
  read_offset = 0;
  write_offset = 0;
}

size_t BitBuffer::nbits() const
{
  return 8*write_head + write_offset;
}

void BitBuffer::reset()
{
  read_head = 0;
  read_offset = 0;
}

bool BitBuffer::byte_aligned() const
{
  return write_offset == 0;
}

bool BitBuffer::read_next_byte(byte_t& b)
{
  if (read_head < write_head && read_head < max_bytes){
    b = data[read_head++];
    return true;
  }
  return false;
}

void BitBuffer::debug_state(std::ostream& os) const
{
  os << "  write_head: " << write_head << std::endl;
  os << "write_offset: " << write_offset << std::endl;
  os << "   read_head: " << read_head << std::endl;
  os << " read_offset: " << read_offset << std::endl;
}

bool BitBuffer::read_next_bit(bool& b)
{
  if (read_head <= write_head && read_head < max_bytes){
    if (read_head == write_head && read_offset >= write_offset) return false;
    b = ((data[read_head]>>read_offset)&1)>0;
    read_offset = (read_offset+1)%8;
    if (read_offset == 0) read_head++;
    return true;
  }
  return false;
}

bool BitBuffer::write_bit(bool bit)
{
  if (write_head < max_bytes) {
    byte_t mask = (0x01 << write_offset);
    if (bit) data[write_head] = data[write_head] | mask;
    if (!bit) data[write_head] = data[write_head] & ~mask;
    write_offset = (write_offset+1) % 8;
    if (write_offset == 0) write_head++;
    return true;
  }
  return false;  
}

bool BitBuffer::write_byte(byte_t b)
{
  if (byte_aligned() && write_head < max_bytes){
    data[write_head++] = b;
    return true;
  }
  return false;
}

bool BitBuffer::pad_to_byte()
{
  if (write_offset < max_bytes){
    while (!byte_aligned()) write_bit(false);
    return true;
  }
  return false;
}

bool BitBuffer::operator==(const BitBuffer& b) const
{
  if (write_head != b.write_head || write_offset != b.write_offset) return false;
  for (size_t i=0; i<write_head; i++){
    if (data[i] != b.data[i]) return false;
  }
  if (!byte_aligned()){
    for (size_t i=0; i<write_offset; i++){
      if( ((data[write_head]>>i)&1) != ((b.data[write_head]>>i)&1)) return false;
    }
  }
  return true;  
}

std::ostream& operator<<(std::ostream& os,BitBuffer& buf)
{
  buf.reset();
  bool bit;
  while(buf.read_next_bit(bit)){
    os << (bit?'1':'0');
  }
  os << std::endl;
  return os;
}
