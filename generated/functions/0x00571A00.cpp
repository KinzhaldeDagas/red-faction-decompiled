// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571A00 rf_color4_set_bytes_return_destination
// UNREALRED VERIFIED [texture-upload-20261028]: Assigns fourcallerbytes tothis+0/+1/+2/+3 andreturnsthis. No channelreordering,clamping or scaling.
_BYTE *__thiscall rf_color4_set_bytes_return_destination(_BYTE *this, char a2, char a3, char a4, char a5)
{
  *this = a2;
  *(this + 1) = a3;
  *(this + 2) = a4;
  *(this + 3) = a5;
  return this;
}

