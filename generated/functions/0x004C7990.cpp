// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C7990 rf_glass_rectangular_face_tessellate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, full rectangular/general quad tessellation, ordered edge selection and stale loop indices, native UV/grid coordinates, pool freshness and delayed launch semantics): 
// Cdecl(face,impactPosition,optionalDirection,suppliedRoom). Assumes valid quad; no own corner-count/rectangle/planarity checks. P0=face64
// head.vertex,P1=head.next20.vertex,P3=head.prev24.vertex,P2=head.next.next.vertex. Saves face AABB center. Builds frame with forward=-face normal,up-hint=normalized(P1-P0);
// W=length(P3-P0),H=length(P1-P0). Counts Nx=min_signed(floor(F32(W*4))+2,16),Ny analogH, saved globals822308/8222C8. No lower/overflow/finite guard. Steps W/(Nx-1),H/(Ny-1) only
// when respective count>2,otherwise0. Global grid822768 is16x16 vertices stride20B, address base+320*i+20*j,XYZ+UV.
// Sets four LOCAL rectangle corners(0,0,0),(W,0,0),(0,H,0),(W,H,0). Bottom/top interior X boundaries consume separate random[-F32.45,+F32.45]*Xstep offsets, in i order; left/right Y
// boundaries separate Y offsets in j order. Interior i-outer,j-inner consumes Y-jitter FIRST then X-jitter, keepsZ0. UV uses ONLY original P0/P2 authored UV differences:
// U=F32((U2-U0)*localX/W+U0),V=F32((V2-V0)*localY/H+V0), no four-corner interpolation or zero-size guard. Then rotates/translates each XYZ by frame/P0 to WORLD; UV remains
// authored-derived. Shared mutable global grid, no reentrancy isolation.
// Common cell/ownership tail shared with the other tessellator: before allocation, traverses ALL existing buckets; shards whose attachment-owner100 equals face.owner68 get random
// axis76,spin88=random[pi,2pi],budget96=floor(random[3,6]),owner100=NULL, then directional launch8840 if direction nonnull else radial73B0(mode0). Existing flags196 not reset. Scans
// worldSolid array156, each element pointer-array108; if any member equals face.owner68 AND differs from supplied room, enables per-cell room resolution. No validation of these
// arrays/owners. Existing-shard reactivation and global grid writes precede all new allocations.
// For each cell i,j, allocator85A0(&shard,suppliedRoom) return BYTE(fresh1/recycled0) is stored but NOT used as success; only output pointerNULL guard exists. Copies four WORLD
// XYZ+UV20B grid vertices in order(i,j),(i,j+1),(i+1,j+1),(i+1,j) to shard116/136/156/176. Flags196=0,center8=sequential sum of four points*.25,orientation20=constructed face frame.
// Radius92 starts fast_distance(vertex0,center) then replaces only when STRICT ORDERED current<candidate for vertices1..3; first NaN sticks, later NaN ignored. Room104 initially
// supplied room; if room-resolution flag set, resolve(world,suppliedRoom,faceAABBcenter,shardCenter,0), store result. NULL resolution releases allocated/recycled node to FREE
// (count--), no owner bucket link/rollback of previously evicted shard. Otherwise bucket-link, inverse-translate/rotate four positions into shard frame (UV unchanged),RGBA56 raw
// white,random axis76,spin88=random[pi,2pi],budget96=floor(random[3,6]),owner100=NULL,bitmap60=shared big-glass handle; launch directional or radial mode0. No pane geometry deletion
// here, allocator-byte failure handling, full record memset or rollback of previous cells/old-shard reactivation. Valid counts<=16 yield at most225 four-corner cells, not 450
// independent triangular shards. Return AL incidental loop/backend/allocator value, not number of cells or reliable bool.
char __cdecl rf_glass_rectangular_face_tessellate(int a1, float *a2, int a3, void *a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  int first_dword; // eax
  float *v17; // eax
  void *v18; // eax
  float *v19; // eax
  double v20; // st7
  double v21; // st7
  float v23; // [esp+8h] [ebp-144h]
  float value; // [esp+Ch] [ebp-140h]
  float valuea; // [esp+Ch] [ebp-140h]
  float *v26; // [esp+10h] [ebp-13Ch]
  float v27; // [esp+14h] [ebp-138h]
  double v28; // [esp+18h] [ebp-134h]
  float v29; // [esp+20h] [ebp-12Ch]
  double v30; // [esp+24h] [ebp-128h]
  float v31; // [esp+2Ch] [ebp-120h]
  float v32; // [esp+30h] [ebp-11Ch]
  float v33; // [esp+34h] [ebp-118h]
  float v34; // [esp+38h] [ebp-114h]
  float v35; // [esp+44h] [ebp-108h]
  float v36; // [esp+48h] [ebp-104h]
  _BYTE v37[4]; // [esp+4Ch] [ebp-100h] BYREF
  float v38[3]; // [esp+50h] [ebp-FCh] BYREF
  float v39[3]; // [esp+5Ch] [ebp-F0h] BYREF
  float v40[3]; // [esp+68h] [ebp-E4h] BYREF
  float v41[3]; // [esp+74h] [ebp-D8h] BYREF
  float v42[3]; // [esp+80h] [ebp-CCh] BYREF
  float copy_result[3]; // [esp+8Ch] [ebp-C0h] BYREF
  float out_vector[3]; // [esp+98h] [ebp-B4h] BYREF
  float sum_result[3]; // [esp+A4h] [ebp-A8h] BYREF
  float v46; // [esp+B0h] [ebp-9Ch]
  int m; // [esp+B4h] [ebp-98h]
  float v48; // [esp+B8h] [ebp-94h]
  char v49; // [esp+BFh] [ebp-8Dh]
  void *v50; // [esp+C0h] [ebp-8Ch]
  int v51; // [esp+C4h] [ebp-88h]
  float v52; // [esp+C8h] [ebp-84h]
  float v53; // [esp+CCh] [ebp-80h]
  float rhs[3]; // [esp+D0h] [ebp-7Ch] BYREF
  float v55; // [esp+DCh] [ebp-70h]
  int j; // [esp+E0h] [ebp-6Ch]
  float v57; // [esp+E4h] [ebp-68h]
  int v58; // [esp+E8h] [ebp-64h]
  float scaled_result[3]; // [esp+ECh] [ebp-60h] BYREF
  const float **v60; // [esp+F8h] [ebp-54h]
  int v61; // [esp+FCh] [ebp-50h]
  float v62; // [esp+100h] [ebp-4Ch]
  float v63; // [esp+104h] [ebp-48h]
  float destination[3]; // [esp+108h] [ebp-44h] BYREF
  float v65[6]; // [esp+114h] [ebp-38h] BYREF
  float v66; // [esp+12Ch] [ebp-20h]
  const float **v67; // [esp+130h] [ebp-1Ch]
  char v68; // [esp+137h] [ebp-15h]
  int v69; // [esp+138h] [ebp-14h]
  int v70; // [esp+13Ch] [ebp-10h]
  float *k; // [esp+140h] [ebp-Ch] BYREF
  int i; // [esp+144h] [ebp-8h]
  float v73; // [esp+148h] [ebp-4h]

  v4 = rf_vector_add((const float *)(a1 + 28), sum_result, (const float *)(a1 + 16));
  rf_vector_multiply_scalar(v4, scaled_result, 0.5);
  v69 = *(_DWORD *)(a1 + 64);
  v67 = *(const float ***)(*(_DWORD *)(a1 + 64) + 20);
  v60 = *(const float ***)(*(_DWORD *)(a1 + 64) + 24);
  v70 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 64) + 20) + 20);
  rf_vector3_copy_return_destination(rhs, *(float **)v69);
  rf_matrix3_construct((char *)destination);
  v5 = rf_vector_subtract(*v60, out_vector, rhs);
  rf_vector_copy(destination, copy_result, v5);
  v6 = rf_vector_subtract(*v67, v42, rhs);
  rf_vector_copy(v65, v41, v6);
  v66 = rf_vector3_length(destination);
  v55 = rf_vector3_length(v65);
  rf_vector_normalize(v65);
  v7 = rf_vector_negate((float *)a1, v40);
  rf_orientation_from_forward_and_up_hint(destination, v7, v65);
  v36 = v66 * 4.0;
  v58 = (int)rf_floor_float(v36) + 2;
  if ( v58 > 16 )
    v58 = 16;
  unk_822308 = v58;
  v35 = v55 * 4.0;
  v61 = (int)rf_floor_float(v35) + 2;
  if ( v61 > 16 )
    v61 = 16;
  unk_8222C8 = v61;
  v57 = 0.0;
  if ( v58 > 2 )
    v57 = v66 / (double)(v58 - 1);
  v73 = 0.0;
  if ( v61 > 2 )
    v73 = v55 / (double)(v61 - 1);
  rf_vector3_set_components_thiscall(unk_822768, 0.0, 0.0, 0.0);
  rf_vector3_set_components_thiscall(&unk_822768[80 * v58 - 80], v66, 0.0, 0.0);
  rf_vector3_set_components_thiscall(&unk_822768[5 * v61 - 5], 0.0, v55, 0.0);
  rf_vector3_set_components_thiscall(&unk_822768[80 * v58 - 85 + 5 * v61], v66, v55, 0.0);
  for ( i = 1; i < v58 - 1; ++i )
  {
    v53 = (double)i * v57;
    v8 = rf_random_float_range(-0.44999999, 0.44999999);
    v34 = v8 * v57 + v53;
    rf_vector3_set_components_thiscall(&unk_822768[80 * i], v34, 0.0, 0.0);
    v23 = v55;
    v9 = rf_random_float_range(-0.44999999, 0.44999999);
    v33 = v9 * v57 + v53;
    rf_vector3_set_components_thiscall(&unk_822768[80 * i - 5 + 5 * v61], v33, v23, 0.0);
  }
  for ( i = 1; i < v61 - 1; ++i )
  {
    v52 = (double)i * v73;
    v10 = rf_random_float_range(-0.44999999, 0.44999999);
    v32 = v10 * v73 + v52;
    rf_vector3_set_components_thiscall(&unk_822768[5 * i], 0.0, v32, 0.0);
    v11 = rf_random_float_range(-0.44999999, 0.44999999);
    v31 = v11 * v73 + v52;
    rf_vector3_set_components_thiscall(&unk_822768[80 * v58 - 80 + 5 * i], v66, v31, 0.0);
  }
  for ( i = 1; i < v58 - 1; ++i )
  {
    for ( j = 1; j < v61 - 1; ++j )
    {
      v30 = (double)j * v73;
      v12 = rf_random_float_range(-0.44999999, 0.44999999);
      v29 = v12 * v73 + v30;
      v28 = (double)i * v57;
      v13 = rf_random_float_range(-0.44999999, 0.44999999);
      v27 = v13 * v57 + v28;
      rf_vector3_set_components_thiscall(&unk_822768[80 * i + 5 * j], v27, v29, 0.0);
    }
  }
  v62 = *(float *)(v70 + 4) - *(float *)(v69 + 4);
  v63 = *(float *)(v70 + 8) - *(float *)(v69 + 8);
  for ( i = 0; i < v58; ++i )
  {
    for ( j = 0; j < v61; ++j )
    {
      flt_82276C[80 * i + 2 + 5 * j] = v62 * unk_822768[80 * i + 5 * j] / v66 + *(float *)(v69 + 4);
      flt_82276C[80 * i + 3 + 5 * j] = v63 * flt_82276C[80 * i + 5 * j] / v55 + *(float *)(v69 + 8);
      rf_vector_rotate_translate_in_place(&unk_822768[80 * i + 5 * j], (int)rhs, (int)destination);
    }
  }
  for ( i = 0; i < rf_glass_shard_bucket_count; ++i )
  {
    for ( k = (float *)rf_glass_shard_bucket_heads[2 * i]; k; k = v26 )
    {
      if ( *((_DWORD *)k + 25) == *(_DWORD *)(a1 + 68) )
      {
        rf_random_unit_vector(k + 19);
        v14 = rf_random_float_range(3.1415927, 6.2831855);
        k[22] = v14;
        value = rf_random_float_range(3.0, 6.0);
        v15 = rf_floor_float(value);
        *((_DWORD *)k + 24) = (int)v15;
        k[25] = 0.0;
        if ( a3 )
          rf_glass_shard_launch_directional_delayed((int)k, (int)a2, a3);
        else
          rf_glass_shard_launch_radial((int)k, a2, 0);
      }
      if ( *(_DWORD *)k == rf_glass_shard_bucket_heads[2 * i] )
        v26 = nullptr;
      else
        v26 = *(float **)k;
    }
  }
  v68 = 0;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(rf_world_solid + 156));
    if ( i >= first_dword )
      break;
    v51 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 156), i);
    for ( j = 0; ; ++j )
    {
      first_dword = rf_receiver_get_first_dword((void *)(v51 + 108));
      if ( j >= first_dword )
        break;
      v50 = *(void **)sub_552200((_DWORD *)(v51 + 108), j);
      LOBYTE(first_dword) = (_BYTE)v50;
      if ( v50 == *(void **)(a1 + 68) && v50 != a4 )
      {
        v68 = 1;
        break;
      }
    }
    if ( v68 == 1 )
      break;
  }
  for ( i = 0; i < v58 - 1; ++i )
  {
    for ( j = 0; j < v61 - 1; ++j )
    {
      LOBYTE(first_dword) = rf_glass_shard_pool_allocate(&k, (int)a4);
      v49 = first_dword;
      if ( !k )
        return first_dword;
      k[49] = 0.0;
      rf_glass_shard_vertex_copy(k + 29, &unk_822768[80 * i + 5 * j]);
      rf_glass_shard_vertex_copy(k + 34, &unk_822768[80 * i + 5 + 5 * j]);
      rf_glass_shard_vertex_copy(k + 39, &unk_822768[80 * i + 85 + 5 * j]);
      rf_glass_shard_vertex_copy(k + 44, &unk_822768[80 * i + 80 + 5 * j]);
      rf_vector3_zero_return_destination(k + 2);
      for ( m = 0; m < 4; ++m )
        rf_vector_accumulate(k + 2, &k[5 * m + 29]);
      v17 = rf_vector_multiply_scalar(k + 2, v39, 0.25);
      rf_vector_copy(k + 2, v38, v17);
      rf_matrix3_copy(k + 5, destination);
      v48 = 0.0;
      v48 = rf_vector_fast_distance(k + 29, k + 2);
      v46 = rf_vector_fast_distance(k + 34, k + 2);
      if ( v48 < (double)v46 )
        v48 = v46;
      v46 = rf_vector_fast_distance(k + 39, k + 2);
      if ( v48 < (double)v46 )
        v48 = v46;
      v46 = rf_vector_fast_distance(k + 44, k + 2);
      if ( v48 < (double)v46 )
        v48 = v46;
      k[23] = v48;
      *((_DWORD *)k + 26) = a4;
      if ( v68 != 1
        || (v18 = rf_world_resolve_cached_room((void *)rf_world_solid, a4, scaled_result, k + 2, 0),
            (*((_DWORD *)k + 26) = v18) != 0) )
      {
        rf_glass_shard_room_bucket_link(k);
        for ( m = 0; m < 4; ++m )
          rf_vector_inverse_translate_rotate_in_place(&k[5 * m + 29], (int)(k + 2), (int)(k + 5));
        v19 = (float *)rf_rgba8_construct_components_return_self(v37, 255, 255, 255, 255);
        k[14] = *v19;
        rf_random_unit_vector(k + 19);
        v20 = rf_random_float_range(3.1415927, 6.2831855);
        k[22] = v20;
        valuea = rf_random_float_range(3.0, 6.0);
        v21 = rf_floor_float(valuea);
        *((_DWORD *)k + 24) = (int)v21;
        k[25] = 0.0;
        *((_DWORD *)k + 15) = rf_glass_blast_texture_handle;
        if ( a3 )
          rf_glass_shard_launch_directional_delayed((int)k, (int)a2, a3);
        else
          rf_glass_shard_launch_radial((int)k, a2, 0);
      }
      else
      {
        rf_glass_shard_pool_release(k);
      }
    }
    LOBYTE(first_dword) = i + 1;
  }
  return first_dword;
}

