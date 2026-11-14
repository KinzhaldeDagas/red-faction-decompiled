// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592440 rf_vfile_test_mode_mask
// UNREALRED VERIFIED [stream-serializers-20261029]: Thiscall vfile,mask. Slot index DWORD object+272 selects32832-byte global record0x189CEB0; returns mode DWORD+0 AND mask without boolean normalization. Does not inspect status,validate index,change mode or read file. Serialization wrappers pass mask1 to choose read versus write.
int __thiscall rf_vfile_test_mode_mask(_DWORD *this, int a2)
{
  return a2 & unk_189CEB0[8208 * *(this + 68)];
}

