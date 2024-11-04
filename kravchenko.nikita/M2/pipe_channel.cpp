#include "pipe_channel.hpp"

kravchenko::PipeChannel::PipeChannel(int fdsPipeRead[2], int fdsPipeWrite[2]):
  fdsToRead_(fdsPipeRead[0]),
  fdsToWrite_(fdsPipeWrite[1])
{
  close(fdsPipeRead[1]);
  fdsPipeRead[1] = -1;
  close(fdsPipeWrite[0]);
  fdsPipeWrite[0] = -1;
}

kravchenko::PipeChannel::~PipeChannel()
{
  close(fdsToRead_);
  close(fdsToWrite_);
}
