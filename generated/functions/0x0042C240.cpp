// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042C240 rf_entity_render_selected_weapon_attachments
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required entity). FIRST clears entity DWORD2064 mask0x200 before ANY admission; null-safe dead predicate does not protect this prior
// dereference. Dead AL must0, primary676!=-1,435AF0 AL nonzero(class1828 mask8), AI+672 holstered-clear AL nonzero. Carrying-body, weapon-holstered-for-actions and
// attached-use-vehicle each reject ONLY EXACT AL1. Weapon-holster predicate exempts attached-use-turret EXACT1 before its entity2064mask800 test. If primary==global911C78 and
// player5168 nonnull, require player BYTE4164 any nonzero. Then cached selected world model50FFA0(primary); player5168 plus BYTE4156 any nonzero overrides model with global911CE4,
// even if initial model absent. Final model0 exits. SIGNED index=0..<live firstDWORD[*(entity668)+468] re-reads entity definition/count each
// bound.420020(entity,index,outAttachmentPoint,outCorrectedPoint,outMatrix) EXACT fullEAX-1 skips this item; EVERY other result admits. No own model-kind/output-validity test. If
// entity FLOAT5060 compares ordered==0 skip extra rotation; ordered nonzero OR UNORDERED enters it (AH44/JNP). Axis pointer is third/forward ROW of the SAME local outMatrix (EBP-40
// matrix, EBP-28 axis); no independent uninitialized axis local. Index0 uses NEGATED angle, positive indices use positive angle;55AA50 does not normalize axis/quaternion.413070
// computes outMatrix LEFT times rotation RIGHT, then copies back. For each admitted item construct fresh render options; global87C640->BYTE4016==EXACT1 ORflags2 and
// color12=(0,32,0,255). ALWAYS ORflags80, copy raw entity RGBA DWORD5236 into options40 and current output matrix into options44. Submit(model,outCorrectedPoint,outMatrix,options),
// ignore result. On loop completion ALWAYS set entity2064mask200, even count<=0 or ALL transforms returned-1; not evidence of an actual draw. Success-through-loop EAX is entity
// pointer bits. Earlier returns retain gate/byte/pointer results, so no uniform success/rendered Boolean. No own pointer/finite/count-cap/rollback or render-state restoration.
char __cdecl rf_entity_render_selected_weapon_attachments(unsigned int *entity)
{
  char result; // al
  int first_dword; // eax
  float *v3; // eax
  float v4; // [esp+0h] [ebp-E4h]
  float v5[9]; // [esp+4h] [ebp-E0h] BYREF
  float v6[9]; // [esp+28h] [ebp-BCh] BYREF
  char v7[12]; // [esp+4Ch] [ebp-98h] BYREF
  _BYTE v8[28]; // [esp+58h] [ebp-8Ch] BYREF
  unsigned int v9; // [esp+74h] [ebp-70h]
  float v10[10]; // [esp+78h] [ebp-6Ch] BYREF
  int v11; // [esp+A0h] [ebp-44h]
  float out_orientation[6]; // [esp+A4h] [ebp-40h] BYREF
  int v13[3]; // [esp+BCh] [ebp-28h] BYREF
  float out_attachment_position[3]; // [esp+C8h] [ebp-1Ch] BYREF
  int attachment_index; // [esp+D4h] [ebp-10h]
  float out_corrected_position[3]; // [esp+D8h] [ebp-Ch] BYREF

  entity[516] &= ~0x200u;
  result = rf_entity_is_dead((int)entity);
  if ( !result && entity[169] != -1 )
  {
    result = rf_entity_class_flags724_has_mask8((int)entity);
    if ( result )
    {
      result = rf_ai_holstered_flag_is_clear((int)(entity + 168));
      if ( result )
      {
        result = rf_entity_is_carrying_body((int)entity);
        if ( result != 1 )
        {
          result = rf_entity_weapon_is_holstered_for_actions((int)entity);
          if ( result != 1 )
          {
            result = rf_entity_has_attached_use_vehicle((int)entity);
            if ( result != 1
              && (entity[169] != dword_911C78 || !entity[1292] || (result = *(_BYTE *)(entity[1292] + 4164)) != 0) )
            {
              rf_vector3_default_construct_noop(out_attachment_position);
              rf_vector3_default_construct_noop(out_corrected_position);
              rf_matrix3_construct((char *)out_orientation);
              v11 = sub_50FFA0(entity[169]);
              result = (char)entity;
              if ( entity[1292] )
              {
                result = *(_BYTE *)(entity[1292] + 4156);
                if ( result )
                  v11 = unk_911CE4;
              }
              if ( v11 )
              {
                for ( attachment_index = 0; ; ++attachment_index )
                {
                  first_dword = rf_receiver_get_first_dword((void *)(entity[167] + 468));
                  if ( attachment_index >= first_dword )
                    break;
                  if ( rf_entity_copy_weapon_attachment_transforms(
                         entity,
                         attachment_index,
                         out_attachment_position,
                         out_corrected_position,
                         out_orientation) != -1 )
                  {
                    if ( *((float *)entity + 1265) != 0.0 )
                    {
                      rf_matrix3_construct((char *)v6);
                      if ( attachment_index <= 0 )
                      {
                        v4 = -*((float *)entity + 1265);
                        rf_matrix3_set_axis_angle_unchecked_axis(v6, (float *)v13, v4);
                      }
                      else
                      {
                        rf_matrix3_set_axis_angle_unchecked_axis(v6, (float *)v13, *((float *)entity + 1265));
                      }
                      v3 = rf_matrix3_argument_times_receiver_to_output(v6, v5, out_orientation);
                      rf_matrix3_copy(out_orientation, v3);
                    }
                    rf_model_render_options_construct(v7);
                    if ( *(_BYTE *)(unk_87C640 + 4016) == 1 )
                    {
                      *(_DWORD *)v7 |= 2u;
                      rf_color4_set_bytes_return_destination(v8, 0, 32, 0, 255);
                    }
                    *(_DWORD *)v7 |= 0x80u;
                    v9 = entity[1309];
                    rf_matrix3_copy(v10, out_orientation);
                    rf_model_handle_render_all_adapter(v11, (int)out_corrected_position, (int)out_orientation, (int)v7);
                  }
                }
                entity[516] |= 0x200u;
                return (char)entity;
              }
            }
          }
        }
      }
    }
  }
  return result;
}

