// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005041A0 rf_trigger_sphere_contains_entity
// UNREALRED VERIFIED [trigger-attachment-20261020] Sphere containment reads current common positions, squared distance <= trigger radius squared. Attachment updates move the center without changing radius. UnrealRed runtime-trigger shape accessor preserves authored extent/radius while replacing only runtime position/rotation.
// UNREALRED VERIFIED [trigger-geometry-20261020] Sphere trigger admission uses common position+0x3C squared distance to trigger common center and radius squared. It does not use the swept physics segment or expand by entity collision size. UE adapter uses the character capsule foot as common position.
void __cdecl rf_trigger_sphere_contains_entity(int a1, int a2)
{
  rf_vector_distance_squared((const float *)(a1 + 60), (const float *)(a2 + 60));
}

