// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B4B30 rf_scene_model_definition_read_chne_binary
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, SFXO/CHNE model wire layout, signed vertex unpacking, vector-return ABI, shared pools and key/geometry conversions): Thiscall same292-byte model,VFile,shared120-byte read context, void return. CHNE chunk reader. Common name/parent/enabled, vertex count176 and obsolete pre3000A seek; sets face count180=0 but DOES NOT WRITE material-reference count188 or pointer192. Reads auxiliary float268, max255-character texture name into local scratch and loads bitmap handle272 without empty-name gate, then ASSIGNS file flags276 (SFXO instead ORs). Common FPS/timing,keyed flag and geometry/pose/key-track allocation follow. Per frame reads origin+8,scale+20 and packed3*vertexCount int16 only for vertex-animated geometry or frame0; static pose40 (translation0,quaternion12,scale28) read per frame when unkeyed, or only frame0 if
// keyed/version<3000E. Radius160 starts0 and is recomputed by scanning all vertices for every frame: helper5B22C0 unpacks signed shorts with per-axis scale plus origin, subtracts that origin through40CF10, computes length and takes max. Animated path uses current frame geometry; static path always frame0 geometry and MULTIPLIES displacement components by pose[frame].scale28/32/36 before length. No translation/quaternion applied in this radius pass. Static radius branch indexes pose[frame] regardless keyed mode: keyed versions reserve only one old pose or no pose for version>=3000E, with no availability guard here. Raw5B5564/5570/5592/55B4 confirm actual pose pointer/scale accesses, not a decompiler uninitialized-temporary artifact. Frame bit31 comes from LOW BIT of file bool helper (default1), preserving low31 bits; differs from unconditional SFXO visibility. Keyed base/keys follow common
// rules. Last reference position148 is frame0 origin when frameCount>0, else zero; this late fallback does not prevent earlier static frame0+4 writes with nonpositive count. Subtype140=1 at end. Material fields188/192 remain retained storage contents from constructor, despite outer5CAF80 postprocess reading them for every model. Shared SFXO/CHNE wire rules: NULL stream returns without writes. Name goes to65-byte field0 with max64 stored characters plus NUL. Parent field65 starts Scene Root; nonempty max255-character scratch overrides it with suffix AFTER FIRST hyphen, or whole scratch if no hyphen. Empty suffix after hyphen is allowed. This copy has no65-byte destination bound. WORD136 bit0=enabled(bool!=0); bits2..15=FPS integer&3FFF (min version30009 hex,default15); bit1=keyed-transform bool&1 (min30009,default0). Version>=40004 reads float start/end into168/172 and signed frame
// count164; older reads integer start/end, divides by stored14-bit FPS with no zero guard, count=end-start+(version>=3000C?1:0), unchecked. Outer VSFX loader rejects40000..40004, but these readers do not. Shared120-byte context offsets:0/4 face144 cursor/base;8/12 pointer-to-material-cursor/material200 base;16/20 pointer-to-blend-float-cursor/base;24/28 pointer-to-single-float-cursor/base;32/36 pointer-to-alpha-float-cursor/base;40/44 material-index DWORD cursor/base;48/52 edge44 cursor/base;56/60 face-pointer DWORD cursor/base;64/68 frame40 cursor/base;72/76 UV-pointer DWORD cursor/base;80/84 pose40 cursor/base;88/92 key-track20 cursor/base;96/100 translation40 cursor/base;104/108 rotation20 cursor/base;112/116 scale40 cursor/base. All cursors/counts are unchecked; no per-read status gate, allocation rollback, old-buffer release or final success result. Frame pool204 reserves count164*40
// by advancing context64; vertex-animation flag276 mask4 allocates6*vertexCount176*frameCount164 bytes at208 and points each frame+4 to its packed triples. Otherwise allocates6*vertexCount once and writes frame0+4 EVEN if frame count<=0. Static nonkeyed transforms reserve per-frame pose40; keyed transform reserves only one old-format pose when version<3000E and one key-track20. Vertex-animated branch does NOT reserve key-track20, but trailing keyed block tests only WORD136 bit1, without rejecting combined flags. Keyed base translation228/quaternion240 read min3000A with global fallbacks, scale256 min3000A with local(1,1,1) fallback. Three key counts read32-bit then TRUNCATE to WORD at key-track0/2/4; loops/cursor increments use UNSIGNED16 counts, so values wrap modulo65536. Key-track pointers8/12/16 borrow context translation40/rotation20/scale40 pools. Translation and scale records: int
// time0 plus three vec3 at4/16/28. Rotation20: int time0; four float quaternion components multiplied16383, trunc-to-int then low16 stored at4/6/8/10 WITHOUT normalization/clamp; five further file floats trunc-to-int then low8 stored12..16 with NO255 scaling. No key sorting/time-range checks, pool bounds or format/flag validation. All version constants in this contract are hexadecimal. Owner132 must already point to outer scene where used; no scene allocation in these readers.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Runtime cross-check with geometry updater5B5F60: zero-count keyed channels dereference old pose220 translation/quaternion/scale. CHNE reader only reserves one old keyed pose for versions<3000E and none for newer keyed versions,so absence of channel keys is not repaired by runtime defaults. Runtime vertex-animation branch also reads frame fields32/36 as dimensions although CHNE does not populate those fade fields. CHNE rendering copies vertexCount into fixed16-point ribbon descriptor5B5E10 without a cap. These findings supplement prior CHNE wire layout and retained-material-reference notes.
void __thiscall rf_scene_model_definition_read_chne_binary(char *this, int *a2, _DWORD *a3)
{
  char *v3; // ecx
  float *v4; // eax
  float *v5; // eax
  float *v6; // ecx
  double v7; // st7
  float *v8; // eax
  float *v9; // ecx
  double v10; // st7
  __int16 v11; // ax
  int v12; // eax
  __int16 v13; // ax
  int v14; // eax
  int float_versioned; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  __int16 v20; // ax
  int v21; // eax
  float *v22; // eax
  float v23; // [esp-14h] [ebp-208h] BYREF
  float v24; // [esp-10h] [ebp-204h]
  float v25; // [esp-Ch] [ebp-200h]
  float v26; // [esp-8h] [ebp-1FCh] BYREF
  float v27; // [esp-4h] [ebp-1F8h]
  float v28; // [esp+0h] [ebp-1F4h]
  float *v29; // [esp+4h] [ebp-1F0h]
  float v30; // [esp+8h] [ebp-1ECh]
  bool v31; // [esp+Eh] [ebp-1E6h]
  bool v32; // [esp+Fh] [ebp-1E5h]
  int v33; // [esp+10h] [ebp-1E4h]
  int v34; // [esp+14h] [ebp-1E0h]
  int int32_versioned; // [esp+18h] [ebp-1DCh]
  bool bool_versioned; // [esp+1Eh] [ebp-1D6h]
  char v37; // [esp+1Fh] [ebp-1D5h]
  char *v38; // [esp+20h] [ebp-1D4h]
  char *v39; // [esp+24h] [ebp-1D0h]
  char *p_Str; // [esp+28h] [ebp-1CCh]
  char v41; // [esp+2Fh] [ebp-1C5h]
  char *v42; // [esp+30h] [ebp-1C4h]
  char *v43; // [esp+34h] [ebp-1C0h]
  char *v44; // [esp+38h] [ebp-1BCh]
  int v45; // [esp+3Ch] [ebp-1B8h]
  _BYTE *v46; // [esp+44h] [ebp-1B0h]
  _BYTE *v47; // [esp+48h] [ebp-1ACh]
  char *v48; // [esp+4Ch] [ebp-1A8h]
  float v49[3]; // [esp+50h] [ebp-1A4h] BYREF
  float v50[3]; // [esp+5Ch] [ebp-198h] BYREF
  float copy_result[3]; // [esp+68h] [ebp-18Ch] BYREF
  float v52[5]; // [esp+74h] [ebp-180h] BYREF
  float out_vector[3]; // [esp+88h] [ebp-16Ch] BYREF
  float out_vertex[5]; // [esp+94h] [ebp-160h] BYREF
  void *v55; // [esp+A8h] [ebp-14Ch]
  void *v56; // [esp+ACh] [ebp-148h]
  float v57[4]; // [esp+B0h] [ebp-144h] BYREF
  float v58[3]; // [esp+C0h] [ebp-134h] BYREF
  int k; // [esp+CCh] [ebp-128h]
  float v60; // [esp+D0h] [ebp-124h] BYREF
  float v61; // [esp+D4h] [ebp-120h]
  float v62; // [esp+D8h] [ebp-11Ch]
  int v63; // [esp+DCh] [ebp-118h]
  int v64; // [esp+E0h] [ebp-114h]
  char *first_character; // [esp+E4h] [ebp-110h]
  int j; // [esp+E8h] [ebp-10Ch]
  char Str; // [esp+ECh] [ebp-108h] BYREF
  _BYTE v68[255]; // [esp+EDh] [ebp-107h] BYREF
  int i; // [esp+1F0h] [ebp-4h]

  v48 = this;
  if ( a2 )
  {
    rf_binary_stream_read_nul_string_to_buffer(a2, v48, 64, 0, nullptr);
    v3 = v48 + 65;
    *(_DWORD *)(v48 + 65) = 1852138323;
    strcpy(v3 + 4, "e Root");
    rf_binary_stream_read_nul_string_to_buffer(a2, &Str, 255, 0, nullptr);
    v46 = v68;
    v47 = &v68[strlen(&Str)];
    v45 = v47 - v68;
    if ( v47 != v68 )
    {
      first_character = rf_cstring_find_first_character(&Str, 45);
      if ( first_character )
      {
        v44 = first_character + 1;
        v43 = v48 + 65;
        v42 = v48 + 65;
        do
        {
          v41 = *v44;
          *v43 = v41;
          ++v44;
          ++v43;
        }
        while ( v41 );
      }
      else
      {
        p_Str = &Str;
        v39 = v48 + 65;
        v38 = v48 + 65;
        do
        {
          v37 = *p_Str;
          *v39 = v37;
          ++p_Str;
          ++v39;
        }
        while ( v37 );
      }
    }
    bool_versioned = rf_binary_stream_read_bool_versioned(a2, 0, 1);
    *((_WORD *)v48 + 68) = bool_versioned | *((_WORD *)v48 + 68) & 0xFFFE;
    *((_DWORD *)v48 + 44) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    if ( !rf_binary_stream_version_at_least(a2, 196618) )
      rf_vfile_seek(a2, 12 * *((_DWORD *)v48 + 44), 1);
    *((_DWORD *)v48 + 45) = 0;
    *((float *)v48 + 67) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    rf_binary_stream_read_nul_string_to_buffer(a2, &Str, 255, 0, nullptr);
    *((_DWORD *)v48 + 68) = rf_bitmap_load_with_optional_mipmap_generation(&Str, (void *)0xFFFFFFFF, 1);
    *((_DWORD *)v48 + 69) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    int32_versioned = rf_binary_stream_read_int32_versioned(a2, 196617, 15);
    *((_WORD *)v48 + 68) = (4 * (int32_versioned & 0x3FFF)) | *((_WORD *)v48 + 68) & 3;
    if ( rf_binary_stream_version_at_least(a2, 262148) )
    {
      *((float *)v48 + 42) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *((float *)v48 + 43) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *((_DWORD *)v48 + 41) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    }
    else
    {
      v64 = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      v63 = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      v34 = (*((_WORD *)v48 + 68) >> 2) & 0x3FFF;
      *((float *)v48 + 42) = (double)v64 / (double)v34;
      v33 = (*((_WORD *)v48 + 68) >> 2) & 0x3FFF;
      *((float *)v48 + 43) = (double)v63 / (double)v33;
      if ( rf_binary_stream_version_at_least(a2, 196620) )
        *((_DWORD *)v48 + 41) = v63 - v64 + 1;
      else
        *((_DWORD *)v48 + 41) = v63 - v64;
    }
    v32 = rf_binary_stream_read_bool_versioned(a2, 196617, 0);
    *((_WORD *)v48 + 68) = (2 * v32) | *((_WORD *)v48 + 68) & 0xFFFD;
    *((_DWORD *)v48 + 51) = a3[17] + 40 * a3[16];
    a3[16] += *((_DWORD *)v48 + 41);
    if ( (*((_DWORD *)v48 + 69) & 4) != 0 )
    {
      v56 = operator new(6 * *((_DWORD *)v48 + 44) * *((_DWORD *)v48 + 41));
      *((_DWORD *)v48 + 52) = v56;
      for ( i = 0; i < *((_DWORD *)v48 + 41); ++i )
        *(_DWORD *)(*((_DWORD *)v48 + 51) + 40 * i + 4) = *((_DWORD *)v48 + 52) + 6 * *((_DWORD *)v48 + 44) * i;
      if ( !rf_binary_stream_version_at_least(a2, 196617) )
        a3[20] += *((_DWORD *)v48 + 41);
    }
    else
    {
      v55 = operator new(6 * *((_DWORD *)v48 + 44));
      *((_DWORD *)v48 + 52) = v55;
      *(_DWORD *)(*((_DWORD *)v48 + 51) + 4) = *((_DWORD *)v48 + 52);
      if ( ((*((_WORD *)v48 + 68) >> 1) & 1) != 0 )
      {
        if ( !rf_binary_stream_version_at_least(a2, 196622) )
          *((_DWORD *)v48 + 55) = a3[21] + 40 * a3[20]++;
        *((_DWORD *)v48 + 56) = a3[23] + 20 * a3[22]++;
      }
      else
      {
        *((_DWORD *)v48 + 55) = a3[21] + 40 * a3[20];
        a3[20] += *((_DWORD *)v48 + 41);
      }
    }
    *((float *)v48 + 40) = 0.0;
    for ( i = 0; i < *((_DWORD *)v48 + 41); ++i )
    {
      if ( (*((_DWORD *)v48 + 69) & 4) != 0 || !i )
      {
        rf_binary_stream_read_vector3_versioned(a2, (float *)(*((_DWORD *)v48 + 51) + 40 * i + 8), 0, unk_1C8FBDC);
        rf_binary_stream_read_vector3_versioned(a2, (float *)(*((_DWORD *)v48 + 51) + 40 * i + 20), 0, unk_1C8FBDC);
        rf_binary_stream_read_int16_array(
          a2,
          *(__int16 **)(*((_DWORD *)v48 + 51) + 40 * i + 4),
          3 * *((_DWORD *)v48 + 44));
      }
      if ( (*((_DWORD *)v48 + 69) & 4) == 0
        && (((*((_WORD *)v48 + 68) >> 1) & 1) == 0 || !rf_binary_stream_version_at_least(a2, 196622) && !i) )
      {
        rf_binary_stream_read_vector3_versioned(a2, (float *)(*((_DWORD *)v48 + 55) + 40 * i), 0, unk_1C8FBDC);
        rf_binary_stream_read_float4_versioned(a2, (float *)(*((_DWORD *)v48 + 55) + 40 * i + 12), 0, unk_1C8FC3C);
        rf_binary_stream_read_vector3_versioned(a2, (float *)(*((_DWORD *)v48 + 55) + 40 * i + 28), 0, unk_1C8FBDC);
      }
      if ( (*((_DWORD *)v48 + 69) & 4) != 0 )
      {
        for ( j = 0; j < *((_DWORD *)v48 + 44); ++j )
        {
          LODWORD(v30) = *((_DWORD *)v48 + 51) + 40 * i + 8;
          v29 = out_vector;
          rf_vector3_copy_return_destination(&v26, (float *)(*((_DWORD *)v48 + 51) + 40 * i + 20));
          rf_vector3_copy_return_destination(&v23, (float *)(*((_DWORD *)v48 + 51) + 40 * i + 8));
          v4 = rf_scene_unpack_signed_vertex(
                 out_vertex,
                 (const __int16 *)(*(_DWORD *)(*((_DWORD *)v48 + 51) + 40 * i + 4) + 6 * j),
                 v23,
                 v24,
                 v25,
                 v26,
                 v27,
                 v28);
          v5 = rf_vector_subtract(v4, v29, (const float *)LODWORD(v30));
          v30 = rf_vector3_length(v5);
          v29 = v6;
          v7 = rf_float_maximum_two_values(*((float *)v48 + 40), v30);
          *((float *)v48 + 40) = v7;
        }
      }
      else
      {
        for ( j = 0; j < *((_DWORD *)v48 + 44); ++j )
        {
          LODWORD(v30) = *((_DWORD *)v48 + 51) + 8;
          v29 = &v60;
          rf_vector3_copy_return_destination(&v26, (float *)(*((_DWORD *)v48 + 51) + 20));
          rf_vector3_copy_return_destination(&v23, (float *)(*((_DWORD *)v48 + 51) + 8));
          v8 = rf_scene_unpack_signed_vertex(
                 v52,
                 (const __int16 *)(*(_DWORD *)(*((_DWORD *)v48 + 51) + 4) + 6 * j),
                 v23,
                 v24,
                 v25,
                 v26,
                 v27,
                 v28);
          rf_vector_subtract(v8, v29, (const float *)LODWORD(v30));
          v60 = v60 * *(float *)(*((_DWORD *)v48 + 55) + 40 * i + 28);
          v61 = v61 * *(float *)(*((_DWORD *)v48 + 55) + 40 * i + 32);
          v62 = v62 * *(float *)(*((_DWORD *)v48 + 55) + 40 * i + 36);
          v30 = rf_vector3_length(&v60);
          v29 = v9;
          v10 = rf_float_maximum_two_values(*((float *)v48 + 40), v30);
          *((float *)v48 + 40) = v10;
        }
      }
      v31 = rf_binary_stream_read_bool_versioned(a2, 0, 1);
      *(_DWORD *)(40 * i + *((_DWORD *)v48 + 51)) = (v31 << 31)
                                                  | *(_DWORD *)(*((_DWORD *)v48 + 51) + 40 * i) & 0x7FFFFFFF;
    }
    if ( ((*((_WORD *)v48 + 68) >> 1) & 1) != 0 )
    {
      rf_binary_stream_read_vector3_versioned(a2, (float *)v48 + 57, 196618, flt_17F10B0);
      rf_binary_stream_read_float4_versioned(a2, (float *)v48 + 60, 196618, flt_18CD810);
      rf_vector3_set_components_return_destination(v58, 1.0, 1.0, 1.0);
      rf_binary_stream_read_vector3_versioned(a2, (float *)v48 + 64, 196618, v58);
      v11 = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      **((_WORD **)v48 + 56) = v11;
      if ( **((_WORD **)v48 + 56) )
      {
        *(_DWORD *)(*((_DWORD *)v48 + 56) + 8) = a3[25] + 40 * a3[24];
        a3[24] += **((unsigned __int16 **)v48 + 56);
        for ( k = 0; k < **((unsigned __int16 **)v48 + 56); ++k )
        {
          v12 = rf_binary_stream_read_int32_versioned(a2, 0, 0);
          *(_DWORD *)(40 * k + *(_DWORD *)(*((_DWORD *)v48 + 56) + 8)) = v12;
          rf_binary_stream_read_vector3_versioned(
            a2,
            (float *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 8) + 40 * k + 4),
            0,
            unk_1C8FBDC);
          rf_binary_stream_read_vector3_versioned(
            a2,
            (float *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 8) + 40 * k + 16),
            0,
            unk_1C8FBDC);
          rf_binary_stream_read_vector3_versioned(
            a2,
            (float *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 8) + 40 * k + 28),
            0,
            unk_1C8FBDC);
        }
      }
      v13 = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      *(_WORD *)(*((_DWORD *)v48 + 56) + 2) = v13;
      if ( *(_WORD *)(*((_DWORD *)v48 + 56) + 2) )
      {
        *(_DWORD *)(*((_DWORD *)v48 + 56) + 12) = a3[27] + 20 * a3[26];
        a3[26] += *(unsigned __int16 *)(*((_DWORD *)v48 + 56) + 2);
        for ( k = 0; k < *(unsigned __int16 *)(*((_DWORD *)v48 + 56) + 2); ++k )
        {
          v14 = rf_binary_stream_read_int32_versioned(a2, 0, 0);
          *(_DWORD *)(20 * k + *(_DWORD *)(*((_DWORD *)v48 + 56) + 12)) = v14;
          rf_float4_construct_zero_zero_zero_one(v57);
          rf_binary_stream_read_float4_versioned(a2, v57, 0, unk_1C8FC3C);
          *(_WORD *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 12) + 20 * k + 4) = (int)(v57[0] * 16383.0);
          *(_WORD *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 12) + 20 * k + 6) = (int)(v57[1] * 16383.0);
          *(_WORD *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 12) + 20 * k + 8) = (int)(v57[2] * 16383.0);
          *(_WORD *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 12) + 20 * k + 10) = (int)(v57[3] * 16383.0);
          float_versioned = (int)rf_binary_stream_read_float_versioned(a2, 0, 0.0);
          *(_BYTE *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 12) + 20 * k + 12) = float_versioned;
          v16 = (int)rf_binary_stream_read_float_versioned(a2, 0, 0.0);
          *(_BYTE *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 12) + 20 * k + 13) = v16;
          v17 = (int)rf_binary_stream_read_float_versioned(a2, 0, 0.0);
          *(_BYTE *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 12) + 20 * k + 14) = v17;
          v18 = (int)rf_binary_stream_read_float_versioned(a2, 0, 0.0);
          *(_BYTE *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 12) + 20 * k + 15) = v18;
          v19 = (int)rf_binary_stream_read_float_versioned(a2, 0, 0.0);
          *(_BYTE *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 12) + 20 * k + 16) = v19;
        }
      }
      v20 = rf_binary_stream_read_int32_versioned(a2, 0, 0);
      *(_WORD *)(*((_DWORD *)v48 + 56) + 4) = v20;
      if ( *(_WORD *)(*((_DWORD *)v48 + 56) + 4) )
      {
        *(_DWORD *)(*((_DWORD *)v48 + 56) + 16) = a3[29] + 40 * a3[28];
        a3[28] += *(unsigned __int16 *)(*((_DWORD *)v48 + 56) + 4);
        for ( k = 0; k < *(unsigned __int16 *)(*((_DWORD *)v48 + 56) + 4); ++k )
        {
          v21 = rf_binary_stream_read_int32_versioned(a2, 0, 0);
          *(_DWORD *)(40 * k + *(_DWORD *)(*((_DWORD *)v48 + 56) + 16)) = v21;
          rf_binary_stream_read_vector3_versioned(
            a2,
            (float *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 16) + 40 * k + 4),
            0,
            unk_1C8FBDC);
          rf_binary_stream_read_vector3_versioned(
            a2,
            (float *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 16) + 40 * k + 16),
            0,
            unk_1C8FBDC);
          rf_binary_stream_read_vector3_versioned(
            a2,
            (float *)(*(_DWORD *)(*((_DWORD *)v48 + 56) + 16) + 40 * k + 28),
            0,
            unk_1C8FBDC);
        }
      }
    }
    if ( *((int *)v48 + 41) <= 0 )
    {
      v22 = rf_vector3_set_components_return_destination(v50, 0.0, 0.0, 0.0);
      rf_vector_copy((float *)v48 + 37, v49, v22);
    }
    else
    {
      rf_vector_copy((float *)v48 + 37, copy_result, (const float *)(*((_DWORD *)v48 + 51) + 8));
    }
    *((_DWORD *)v48 + 35) = 1;
  }
}

