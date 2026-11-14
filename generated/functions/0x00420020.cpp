// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00420020 rf_entity_copy_weapon_attachment_transforms
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Actual Cdecl FIVE arguments(entity,signed attachmentIndex,outAttachmentPosition,outCorrectedPosition,outOrientationMatrix), fullEAX0
// success/-1 failure; stored3arg type wrong. Construct local matrix with no-write constructor. Signed count from entity pointer+668 inline list+468 must be STRICTLY>attachmentIndex;
// no attachmentIndex>=0 check, so negative indices may pass and index unchecked receiver+4+4*index. Failure returns-1 before own output writes. Then50FFA0(entity primary676) must
// return NONZERO cached world-weapon model handle; zero returns-1. Accessor independently accepts only signed weapon IDs[0,64), nonempty worldmesh name; it does not load resources.
// First5651D0(entity model128,selected inline tag,entity orientation72,entity position60,localAttachmentMatrix,outAttachmentPosition), return ignored; composer does not validate
// lower transform outcome. Copy current outAttachmentPosition into outCorrectedPosition, then copy localAttachmentMatrix into outOrientationMatrix, in that order. RE-READ entity
// primary676 AFTER these output writes and call510000 for world-weapon grip_1 index; delegate may lazily mutate weapon-record grip cache. Exact grip==-1 still returns success0,
// retaining copied outputs. Any other grip value invokes5651D0(captured initial worldWeaponModel,grip,localAttachmentMatrix,current outAttachmentPosition,unused
// localMatrix,localGripPoint), ignored pointer return. Compute FLOAT32 vector delta=localGripPoint-current outAttachmentPosition, then sequential FLOAT32 in-place subtract delta from
// outCorrectedPosition; output orientation is NOT replaced by grip orientation. For ordinary disjoint buffers, attachment output and attachment orientation remain first transform,
// corrected output becomes stored attachment point minus stored grip displacement. Preserve native stores/rounding rather than algebraically collapsing to unrounded2*point-grip.
// Outputs/source are not globally snapshotted or alias-checked: matrix/corrected output writes precede later position and primary reads, so overlapping outputs/entity storage can
// affect the correction and even later grip lookup. Failure paths do not initialize outputs; success does not prove valid model transform, distinct output pointers or finite data.
int __cdecl rf_entity_copy_weapon_attachment_transforms(
        const unsigned int *entity,
        int attachment_index,
        float *out_attachment_position,
        float *out_corrected_position,
        float *out_orientation)
{
  int *v6; // eax
  float copy_result[3]; // [esp+0h] [ebp-74h] BYREF
  float out_vector[3]; // [esp+Ch] [ebp-68h] BYREF
  char v9[36]; // [esp+18h] [ebp-5Ch] BYREF
  float lhs[3]; // [esp+3Ch] [ebp-38h] BYREF
  int v11; // [esp+48h] [ebp-2Ch]
  int v12; // [esp+4Ch] [ebp-28h]
  float v13[9]; // [esp+50h] [ebp-24h] BYREF

  rf_matrix3_construct((char *)v13);
  if ( rf_receiver_get_first_dword((void *)(entity[167] + 468)) <= attachment_index )
    return -1;
  v11 = sub_50FFA0(entity[169]);
  if ( !v11 )
    return -1;
  v6 = (int *)rf_inline_dword_array4_element_address_unchecked((void *)(entity[167] + 468), attachment_index);
  rf_vmesh_compose_prop_world_transform(
    entity[32],
    *v6,
    (float *)entity + 18,
    (int)(entity + 15),
    (int)v13,
    out_attachment_position);
  rf_vector_copy(out_corrected_position, copy_result, out_attachment_position);
  rf_matrix3_copy(out_orientation, v13);
  v12 = sub_510000(entity[169]);
  if ( v12 != -1 )
  {
    rf_vector3_default_construct_noop(lhs);
    rf_matrix3_construct(v9);
    rf_vmesh_compose_prop_world_transform(v11, v12, v13, (int)out_attachment_position, (int)v9, lhs);
    rf_vector_subtract(lhs, out_vector, out_attachment_position);
    rf_vector_subtract_in_place(out_corrected_position, out_vector);
  }
  return 0;
}

