#ifndef BITBUFFER_H
#define BITBUFFER_H

#include <iostream>
#include <cstdint>

typedef uint8_t byte_t;

class BitBuffer {
public:
  BitBuffer() {init(1024);}
  BitBuffer(size_t nbytes) {init(nbytes);}
  BitBuffer(const BitBuffer&);
  ~BitBuffer() {delete data;}

  bool operator==(const BitBuffer&) const;
  
  void reset();
  size_t nbits() const;
  bool byte_aligned() const;
  bool read_next_byte(byte_t&);
  bool read_next_bit(bool& b);
  
  bool write_bit(bool);
  bool write_byte(byte_t);    
  bool pad_to_byte();


  void debug_state(std::ostream&) const;
 

private:
  void init(size_t);
  size_t max_bytes;
  size_t read_head;
  size_t read_offset;
  size_t write_head;
  size_t write_offset;
  
  byte_t* data;
  

};

std::ostream& operator<<(std::ostream&,BitBuffer&);

#endif
