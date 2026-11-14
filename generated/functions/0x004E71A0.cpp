// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E71A0 sub_4E71A0
// UNREALRED VERIFIED [rocket-generation-20260930] Lock reset clears Player+3997 ready and +3996 active, sets +4000 target handle to -1, and arms +4008 scan timer at zero. Direct callers include reload 0x4E7023, holster 0x4E7206, and lock update invalid-player/entity/weapon or post-launch paths in 0x4EAF20. This reset cancels state without synthesizing an early-release shot. Unreal imported-level generation cancellation is a host lifetime adaptation; these callers alone do not establish a native streamed-generation protocol.
int __cdecl sub_4E71A0(int a1)
{
  int result; // eax

  if ( a1 )
  {
    *(_BYTE *)(a1 + 3997) = 0;
    *(_BYTE *)(a1 + 3996) = 0;
    *(_DWORD *)(a1 + 4000) = -1;
    return rf_replicator_arm_milliseconds((int *)(a1 + 4008), 0);
  }
  return result;
}

