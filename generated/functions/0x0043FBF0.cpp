// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043FBF0 sub_43FBF0
// UNREALRED VERIFIED [burn-motion-20261029]: Rebinds a fire owner to the supplied common-object handle, reruns attachment lookup, rewrites each emitter owner, marks fade byte+0x2C=1 and fade age+0x30=0; unresolved replacement destroys the fire record. This is separate from live self-burn damage and must be integrated with native corpse ownership, not a fixed burn timer starting at ignition.
// UNREALRED VERIFIED [combat-burn-owner-20261104]: Logical transfer resolves replacement common object; missing replacement releases. Valid transfer updates owner, attempts binding but ignores boolean failure, rewrites all4emitter parents, starts fading at age0 and sets replacement commonflag0x200. Preserves ignition-source handle, mutated controls and voice; no emitter/audio restart. Must not start this at an earlier host visual ragdoll allocation.
// [UnrealRed burn initialization availability 2026-11-12; full original-byte ASM] Transfer resolves replacement then writes owner+4 of ALL4 emitter pointers unconditionally, rebinds bones while ignoring failure and starts fade. Real native partialNULL transfer is an unsafe/undefined domain, not a successful ready transfer. A host initialization reservation is not yet a native active burn record and must not silently reparent an unfinished source-bound continuation to another lifetime.
float *__cdecl sub_43FBF0(int a1, int a2)
{
  int v3; // [esp+0h] [ebp-8h]

  v3 = rf_object_resolve_handle(a2);
  if ( !v3 )
    return rf_burn_effect_release_record((float *)a1, 0);
  *(_DWORD *)(a1 + 16) = a2;
  sub_43ECF0((_DWORD *)a1, v3);
  *(_DWORD *)(*(_DWORD *)a1 + 4) = a2;
  *(_DWORD *)(*(_DWORD *)(a1 + 4) + 4) = a2;
  *(_DWORD *)(*(_DWORD *)(a1 + 8) + 4) = a2;
  *(_DWORD *)(*(_DWORD *)(a1 + 12) + 4) = a2;
  *(_BYTE *)(a1 + 44) = 1;
  *(float *)(a1 + 48) = 0.0;
  *(_DWORD *)(v3 + 668) |= 0x200u;
  return (float *)v3;
}

