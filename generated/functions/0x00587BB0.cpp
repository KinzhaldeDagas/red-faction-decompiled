// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587BB0 rf_character_system_release_instances_and_resources
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): While global instance-list head18CDA28 nonNULL, invokes scalar deleting destructor566C00(head,1), relying on instance cleanup to unlink/update head. Then releases loaded base characters without flag8 and invokes named-owned clip-buffer sweep5BA490. Returns final clip sweep loop value. Can loop indefinitely if head destructor fails to unlink (e.g. no base-character pointer). No independent list integrity/ownership checks.
int rf_character_system_release_instances_and_resources()
{
  while ( unk_18CDA28 )
    rf_character_instance_scalar_deleting_destructor(unk_18CDA28, 1);
  rf_character_cache_release_without_flag8();
  return rf_animation_clip_pool_release_named_owned_buffers();
}

