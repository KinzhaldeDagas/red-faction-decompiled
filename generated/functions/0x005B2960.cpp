// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B2960 rf_scene_model_definition_read_sfxo_binary
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, SFXO/CHNE model wire layout, signed vertex unpacking, vector-return ABI, shared pools and key/geometry conversions): Thiscall292-byte model, VFile and shared120-byte read context, void return. SFXO chunk reader used by5CAF80. After common name/parent/enabled reads, stores vertex count176 and for version<3000A seeks12*vertexCount obsolete bytes. Reads face count180, binds faces184=context4+144*context0 and advances cursor0. For version<3000D reserves one UV-pointer slot212 and allocates owned24*faceCount UV bytes216. Each144-byte face reads three int indices20/24/28; old versions read six UV floats into owned storage as U/V pairs at offsets j*4 and j*4+12. Reads nine RGB component floats interleaved into byte triples84/87/90: multiply255 then truncate integer and low8, NO clamp. Reads vectors96/108,float120,material
// field32 (decrement for version<40000),then four ints128/132/136/140. First negative material field only sprintf-formats a local diagnostic; no print/fatal/status change. Common FPS/timing next. Reads material-reference count188, initializes192=NULL, reserves positive count from context40/44. Version>=40000 reads raw DWORD material indices. Older versions build each referenced material in shared200-byte pool via pointer-to-cursor context8/12 and map its allocated global index into192. Legacy material type2 reads int RGB to bytes9..11 with alpha255. Other types read bool8(min30003), primary name20(max32) and load handle16 with context-1/mipmap1; type1 optionally loads secondary name72/handle68, others clear secondary fields. Texture auxiliary triples56/60/64 and108/112/116 gate at30012 with defaults0/1/0; older files read two ints after names and mirror them to both textures. Detail
// floats132/136/140 and name144(max32,default empty) gate30007; empty detail yields handle180=-1, otherwise loads bitmap. Legacy type1 blend curve count124=frameCount, reserves positive floats from context16/20, reads/clamps finite values0..1. All legacy materials reserve one float188 via context24/28 (read min30011/default0), and frameCount alpha floats196 via context32/36. Reads pivot148,radius160; for version<30002 maps extra old flags1/2 to model276 masks10h/20h, then ORs file flags into276, preserving prior bits. Exactly version3000A with flag1 reads two saved fade defaults. Reads edge count196; binds edge44 records200=context52+44*cursor48 and advances. Each edge reads ints0/4,zeroes DWORD8 and BYTE24,reads floats28/32,then count36 and borrowed face-pointer list40 from context56/60; each int face index becomes face184+144*index. Face fields132/136/140 likewise become edge200+44*index
// WITHOUT sentinel/range checks. Common keyed flag and geometry allocation follow. For version>=3000D UV-table size is frameCount when flag100h set, else1; owned216 contains24*faceCount*sliceCount bytes, slot212 points to each slice. Per frame, animated vertices or first frame read origin frame+8,scale+20,3*vertexCount int16 words; flags801h read fades+32/+36 min3000B using saved defaults, and flag800h on frame0 reads axis280 min40001 then calls normalize. Version>=3000D reads UV pairs on each frame with flag100h, otherwise only frame0. Static pose reads occur when not keyed, or only frame0 for keyed version<3000E. Version<30009 skips one obsolete byte/frame. Sets each processed frame DWORD0 high bit31 unconditionally; no visible-bool read here. Version<40005 reads/clamps one alpha float/frame and writes it to EVERY referenced scene material at material.alphaPtr196+4*frame, using
// owner132/material pool140. Keyed records follow common rules. Finally sets subtype140=0, even if stream has accumulated error. No payload-length parameter, count caps, index checks or early I/O-error return; context/pointers can be partially advanced. Shared SFXO/CHNE wire rules: NULL stream returns without writes. Name goes to65-byte field0 with max64 stored characters plus NUL. Parent field65 starts Scene Root; nonempty max255-character scratch overrides it with suffix AFTER FIRST hyphen, or whole scratch if no hyphen. Empty suffix after hyphen is allowed. This copy has no65-byte destination bound. WORD136 bit0=enabled(bool!=0); bits2..15=FPS integer&3FFF (min version30009 hex,default15); bit1=keyed-transform bool&1 (min30009,default0). Version>=40004 reads float start/end into168/172 and signed frame count164; older reads integer start/end, divides by stored14-bit FPS with no zero
// guard, count=end-start+(version>=3000C?1:0), unchecked. Outer VSFX loader rejects40000..40004, but these readers do not. Shared120-byte context offsets:0/4 face144 cursor/base;8/12 pointer-to-material-cursor/material200 base;16/20 pointer-to-blend-float-cursor/base;24/28 pointer-to-single-float-cursor/base;32/36 pointer-to-alpha-float-cursor/base;40/44 material-index DWORD cursor/base;48/52 edge44 cursor/base;56/60 face-pointer DWORD cursor/base;64/68 frame40 cursor/base;72/76 UV-pointer DWORD cursor/base;80/84 pose40 cursor/base;88/92 key-track20 cursor/base;96/100 translation40 cursor/base;104/108 rotation20 cursor/base;112/116 scale40 cursor/base. All cursors/counts are unchecked; no per-read status gate, allocation rollback, old-buffer release or final success result. Frame pool204 reserves count164*40 by advancing context64; vertex-animation flag276 mask4
// allocates6*vertexCount176*frameCount164 bytes at208 and points each frame+4 to its packed triples. Otherwise allocates6*vertexCount once and writes frame0+4 EVEN if frame count<=0. Static nonkeyed transforms reserve per-frame pose40; keyed transform reserves only one old-format pose when version<3000E and one key-track20. Vertex-animated branch does NOT reserve key-track20, but trailing keyed block tests only WORD136 bit1, without rejecting combined flags. Keyed base translation228/quaternion240 read min3000A with global fallbacks, scale256 min3000A with local(1,1,1) fallback. Three key counts read32-bit then TRUNCATE to WORD at key-track0/2/4; loops/cursor increments use UNSIGNED16 counts, so values wrap modulo65536. Key-track pointers8/12/16 borrow context translation40/rotation20/scale40 pools. Translation and scale records: int time0 plus three vec3 at4/16/28. Rotation20: int time0;
// four float quaternion components multiplied16383, trunc-to-int then low16 stored at4/6/8/10 WITHOUT normalization/clamp; five further file floats trunc-to-int then low8 stored12..16 with NO255 scaling. No key sorting/time-range checks, pool bounds or format/flag validation. All version constants in this contract are hexadecimal. Owner132 must already point to outer scene where used; no scene allocation in these readers.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Runtime cross-check with geometry updater5B5F60: keyed transform sampling uses base values228/240/256,then channel transforms. A zero translation/rotation/scale key count falls back to OLD pose220 for that channel,not base values or identity. Reader reserves pose220 only for keyed versions<3000E,leaving constructor zero for newer keyed versions; updater has no fallback-pointer validation. Keyed flag affects trailing key reads,while geometry allocation chooses vertex-animated flag4 first without rejecting combined flags. This supplements existing SFXO wire-layout/ownership contract; no bytes changed.
void __thiscall rf_scene_model_definition_read_sfxo_binary(char *self, int *stream, unsigned int *context)
{
  double float_versioned; // st7
  double v4; // st7
  int v5; // eax
  int v6; // eax
  double v7; // st7
  double v8; // st7
  int v9; // eax
  int v10; // eax
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  char v23; // [esp+3Fh] [ebp-1ADh]
  char *v24; // [esp+44h] [ebp-1A8h]
  char *p_Buffer; // [esp+48h] [ebp-1A4h]
  char v26; // [esp+4Fh] [ebp-19Dh]
  char *v27; // [esp+54h] [ebp-198h]
  char *v28; // [esp+58h] [ebp-194h]
  float v30[4]; // [esp+80h] [ebp-16Ch] BYREF
  float v31[3]; // [esp+90h] [ebp-15Ch] BYREF
  int m; // [esp+9Ch] [ebp-150h]
  int v33; // [esp+A0h] [ebp-14Ch]
  float v34; // [esp+A4h] [ebp-148h]
  int k; // [esp+A8h] [ebp-144h]
  int v36; // [esp+ACh] [ebp-140h]
  int v37; // [esp+B0h] [ebp-13Ch]
  int v38; // [esp+B4h] [ebp-138h]
  int v39; // [esp+B8h] [ebp-134h]
  int v40; // [esp+BCh] [ebp-130h]
  unsigned int v41; // [esp+C0h] [ebp-12Ch]
  int v42; // [esp+C4h] [ebp-128h]
  int int32_versioned; // [esp+C8h] [ebp-124h]
  int v44; // [esp+CCh] [ebp-120h]
  char *first_character; // [esp+D0h] [ebp-11Ch]
  int j; // [esp+D4h] [ebp-118h]
  char v47; // [esp+DBh] [ebp-111h]
  char Buffer; // [esp+DCh] [ebp-110h] BYREF
  _BYTE v49[3]; // [esp+DDh] [ebp-10Fh] BYREF
  int i; // [esp+1E0h] [ebp-Ch]
  float v51; // [esp+1E4h] [ebp-8h]
  float v52; // [esp+1E8h] [ebp-4h]

  if ( stream )
  {
    rf_binary_stream_read_nul_string_to_buffer(stream, self, 64, 0, nullptr);
    strcpy(self + 65, "Scene Root");
    rf_binary_stream_read_nul_string_to_buffer(stream, &Buffer, 255, 0, nullptr);
    if ( &v49[strlen(&Buffer)] != v49 )
    {
      first_character = rf_cstring_find_first_character(&Buffer, 45);
      if ( first_character )
      {
        v28 = first_character + 1;
        v27 = self + 65;
        do
        {
          v26 = *v28;
          *v27++ = *v28++;
        }
        while ( v26 );
      }
      else
      {
        p_Buffer = &Buffer;
        v24 = self + 65;
        do
        {
          v23 = *p_Buffer;
          *v24++ = *p_Buffer++;
        }
        while ( v23 );
      }
    }
    *((_WORD *)self + 68) = rf_binary_stream_read_bool_versioned(stream, 0, 1) | *((_WORD *)self + 68) & 0xFFFE;
    *((_DWORD *)self + 44) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
    if ( !rf_binary_stream_version_at_least(stream, 196618) )
      rf_vfile_seek(stream, 12 * *((_DWORD *)self + 44), 1);
    *((_DWORD *)self + 45) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
    *((_DWORD *)self + 46) = context[1] + 144 * *context;
    *context += *((_DWORD *)self + 45);
    if ( !rf_binary_stream_version_at_least(stream, 196621) )
    {
      *((_DWORD *)self + 53) = context[19] + 4 * context[18]++;
      *((_DWORD *)self + 54) = operator new(24 * *((_DWORD *)self + 45));
      **((_DWORD **)self + 53) = *((_DWORD *)self + 54);
    }
    v47 = 0;
    for ( i = 0; i < *((_DWORD *)self + 45); ++i )
    {
      v44 = *((_DWORD *)self + 46) + 144 * i;
      *(_DWORD *)(v44 + 20) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *(_DWORD *)(v44 + 24) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *(_DWORD *)(v44 + 28) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      if ( !rf_binary_stream_version_at_least(stream, 196621) )
      {
        for ( j = 0; j < 3; ++j )
        {
          float_versioned = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
          *(float *)(**((_DWORD **)self + 53) + 24 * i + 4 * j) = float_versioned;
          v4 = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
          *(float *)(**((_DWORD **)self + 53) + 24 * i + 4 * j + 12) = v4;
        }
      }
      for ( j = 0; j < 3; ++j )
      {
        *(_BYTE *)(j + v44 + 84) = (int)(rf_binary_stream_read_float_versioned(stream, 0, 0.0) * 255.0);
        *(_BYTE *)(j + v44 + 87) = (int)(rf_binary_stream_read_float_versioned(stream, 0, 0.0) * 255.0);
        *(_BYTE *)(j + v44 + 90) = (int)(rf_binary_stream_read_float_versioned(stream, 0, 0.0) * 255.0);
      }
      rf_binary_stream_read_vector3_versioned(stream, (float *)(v44 + 96), 0, unk_1C8FBDC);
      rf_binary_stream_read_vector3_versioned(stream, (float *)(v44 + 108), 0, unk_1C8FBDC);
      *(float *)(v44 + 120) = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
      *(_DWORD *)(v44 + 32) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      if ( !rf_binary_stream_version_at_least(stream, 0x40000) )
        --*(_DWORD *)(v44 + 32);
      if ( *(int *)(v44 + 32) < 0 && !v47 )
      {
        sprintf(&Buffer, "face in mesh %s has no material\n", self);
        v47 = 1;
      }
      *(_DWORD *)(v44 + 128) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *(_DWORD *)(v44 + 132) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *(_DWORD *)(v44 + 136) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *(_DWORD *)(v44 + 140) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
    }
    *((_WORD *)self + 68) = (4 * (rf_binary_stream_read_int32_versioned(stream, 196617, 15) & 0x3FFF))
                          | *((_WORD *)self + 68) & 3;
    if ( rf_binary_stream_version_at_least(stream, 262148) )
    {
      *((float *)self + 42) = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
      *((float *)self + 43) = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
      *((_DWORD *)self + 41) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
    }
    else
    {
      int32_versioned = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      v42 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *((float *)self + 42) = (double)int32_versioned / (double)((*((_WORD *)self + 68) >> 2) & 0x3FFF);
      *((float *)self + 43) = (double)v42 / (double)((*((_WORD *)self + 68) >> 2) & 0x3FFF);
      if ( rf_binary_stream_version_at_least(stream, 196620) )
        *((_DWORD *)self + 41) = v42 - int32_versioned + 1;
      else
        *((_DWORD *)self + 41) = v42 - int32_versioned;
    }
    *((_DWORD *)self + 47) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
    *((_DWORD *)self + 48) = 0;
    if ( *((int *)self + 47) > 0 )
    {
      *((_DWORD *)self + 48) = context[11] + 4 * context[10];
      context[10] += *((_DWORD *)self + 47);
      if ( rf_binary_stream_version_at_least(stream, 0x40000) )
      {
        rf_vfile_read_buffered_bytes_versioned(stream, *((char **)self + 48), 4 * *((_DWORD *)self + 47), 0, 0);
      }
      else
      {
        for ( i = 0; i < *((_DWORD *)self + 47); ++i )
        {
          v41 = context[3] + 200 * *(_DWORD *)context[2];
          *(_DWORD *)(v41 + 120) = (*((_WORD *)self + 68) >> 2) & 0x3FFF;
          *(_DWORD *)v41 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
          if ( *(_DWORD *)v41 == 2 )
          {
            v38 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
            v39 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
            v40 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
            rf_color4_set_bytes_return_destination((_BYTE *)(v41 + 9), v38, v39, v40, 255);
            *(_DWORD *)(v41 + 184) = 1;
            *(_DWORD *)(v41 + 188) = context[7] + 4 * (*(_DWORD *)context[6])++;
            **(float **)(v41 + 188) = rf_binary_stream_read_float_versioned(stream, 196625, 0.0);
            *(_DWORD *)(v41 + 192) = *((_DWORD *)self + 41);
            *(_DWORD *)(v41 + 196) = context[9] + 4 * *(_DWORD *)context[8];
            *(_DWORD *)context[8] += *((_DWORD *)self + 41);
          }
          else
          {
            *(_BYTE *)(v41 + 8) = rf_binary_stream_read_bool_versioned(stream, 196611, 0);
            rf_binary_stream_read_nul_string_to_buffer(stream, (char *)(v41 + 20), 32, 0, nullptr);
            *(_DWORD *)(v41 + 16) = rf_bitmap_load_with_optional_mipmap_generation(
                                      (char *)(v41 + 20),
                                      (void *)0xFFFFFFFF,
                                      1);
            *(_DWORD *)(v41 + 56) = rf_binary_stream_read_int32_versioned(stream, 196626, 0);
            *(float *)(v41 + 60) = rf_binary_stream_read_float_versioned(stream, 196626, 1.0);
            *(_DWORD *)(v41 + 64) = rf_binary_stream_read_int32_versioned(stream, 196626, 0);
            if ( *(_DWORD *)v41 == 1 )
            {
              rf_binary_stream_read_nul_string_to_buffer(stream, (char *)(v41 + 72), 32, 0, nullptr);
              if ( v41 + 72 + strlen((const char *)(v41 + 72)) + 1 == v41 + 73 )
                *(_DWORD *)(v41 + 68) = -1;
              else
                *(_DWORD *)(v41 + 68) = rf_bitmap_load_with_optional_mipmap_generation(
                                          (char *)(v41 + 72),
                                          (void *)0xFFFFFFFF,
                                          1);
              *(_DWORD *)(v41 + 108) = rf_binary_stream_read_int32_versioned(stream, 196626, 0);
              *(float *)(v41 + 112) = rf_binary_stream_read_float_versioned(stream, 196626, 1.0);
              *(_DWORD *)(v41 + 116) = rf_binary_stream_read_int32_versioned(stream, 196626, 0);
            }
            else
            {
              *(_BYTE *)(v41 + 72) = 0;
              *(_DWORD *)(v41 + 68) = -1;
              *(_DWORD *)(v41 + 108) = 0;
              *(float *)(v41 + 112) = 1.0;
              *(_DWORD *)(v41 + 116) = 0;
            }
            if ( !rf_binary_stream_version_at_least(stream, 196626) )
            {
              *(_DWORD *)(v41 + 56) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
              *(_DWORD *)(v41 + 108) = *(_DWORD *)(v41 + 56);
              *(_DWORD *)(v41 + 64) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
              *(_DWORD *)(v41 + 116) = *(_DWORD *)(v41 + 64);
            }
            *(float *)(v41 + 132) = rf_binary_stream_read_float_versioned(stream, 196615, 0.0);
            *(float *)(v41 + 136) = rf_binary_stream_read_float_versioned(stream, 196615, 0.0);
            *(float *)(v41 + 140) = rf_binary_stream_read_float_versioned(stream, 196615, 0.0);
            rf_binary_stream_read_nul_string_to_buffer(stream, (char *)(v41 + 144), 32, 196615, byte_643F96);
            if ( v41 + 144 + strlen((const char *)(v41 + 144)) + 1 == v41 + 145 )
              *(_DWORD *)(v41 + 180) = -1;
            else
              *(_DWORD *)(v41 + 180) = rf_bitmap_load_with_optional_mipmap_generation(
                                         (char *)(v41 + 144),
                                         (void *)0xFFFFFFFF,
                                         1);
            if ( *(_DWORD *)v41 == 1 )
            {
              *(_DWORD *)(v41 + 124) = *((_DWORD *)self + 41);
              if ( *(int *)(v41 + 124) > 0 )
              {
                *(_DWORD *)(v41 + 128) = context[5] + 4 * *(_DWORD *)context[4];
                *(_DWORD *)context[4] += *(_DWORD *)(v41 + 124);
                for ( j = 0; j < *(_DWORD *)(v41 + 124); ++j )
                {
                  *(float *)(*(_DWORD *)(v41 + 128) + 4 * j) = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
                  *(float *)(*(_DWORD *)(v41 + 128) + 4 * j) = rf_float_maximum_two_values(
                                                                 *(float *)(*(_DWORD *)(v41 + 128) + 4 * j),
                                                                 0.0);
                  *(float *)(*(_DWORD *)(v41 + 128) + 4 * j) = rf_float_minimum_two_values(
                                                                 *(float *)(*(_DWORD *)(v41 + 128) + 4 * j),
                                                                 1.0);
                }
              }
            }
            *(_DWORD *)(v41 + 184) = 1;
            *(_DWORD *)(v41 + 188) = context[7] + 4 * (*(_DWORD *)context[6])++;
            **(float **)(v41 + 188) = rf_binary_stream_read_float_versioned(stream, 196625, 0.0);
            *(_DWORD *)(v41 + 192) = *((_DWORD *)self + 41);
            *(_DWORD *)(v41 + 196) = context[9] + 4 * *(_DWORD *)context[8];
            *(_DWORD *)context[8] += *((_DWORD *)self + 41);
          }
          *(_DWORD *)(*((_DWORD *)self + 48) + 4 * i) = (*(_DWORD *)context[2])++;
        }
      }
    }
    rf_binary_stream_read_vector3_versioned(stream, (float *)self + 37, 0, unk_1C8FBDC);
    *((float *)self + 40) = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
    if ( !rf_binary_stream_version_at_least(stream, 196610) )
    {
      v37 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      if ( (v37 & 1) != 0 )
        *((_DWORD *)self + 69) |= 0x10u;
      if ( (v37 & 2) != 0 )
        *((_DWORD *)self + 69) |= 0x20u;
    }
    *((_DWORD *)self + 69) |= rf_binary_stream_read_int32_versioned(stream, 0, 0);
    v51 = -1.0;
    v52 = -1.0;
    if ( (*((_DWORD *)self + 69) & 1) != 0 && rf_vfile_get_slot_version(stream) == 196618 )
    {
      v51 = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
      v52 = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
    }
    *((_DWORD *)self + 49) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
    *((_DWORD *)self + 50) = context[13] + 44 * context[12];
    context[12] += *((_DWORD *)self + 49);
    for ( i = 0; i < *((_DWORD *)self + 49); ++i )
    {
      v5 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *(_DWORD *)(44 * i + *((_DWORD *)self + 50)) = v5;
      v6 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *(_DWORD *)(*((_DWORD *)self + 50) + 44 * i + 4) = v6;
      *(_DWORD *)(*((_DWORD *)self + 50) + 44 * i + 8) = 0;
      *(_BYTE *)(*((_DWORD *)self + 50) + 44 * i + 24) = 0;
      v7 = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
      *(float *)(*((_DWORD *)self + 50) + 44 * i + 28) = v7;
      v8 = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
      *(float *)(*((_DWORD *)self + 50) + 44 * i + 32) = v8;
      v9 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *(_DWORD *)(*((_DWORD *)self + 50) + 44 * i + 36) = v9;
      *(_DWORD *)(*((_DWORD *)self + 50) + 44 * i + 40) = context[15] + 4 * context[14];
      context[14] += *(_DWORD *)(*((_DWORD *)self + 50) + 44 * i + 36);
      for ( j = 0; j < *(_DWORD *)(*((_DWORD *)self + 50) + 44 * i + 36); ++j )
      {
        v10 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)self + 50) + 44 * i + 40) + 4 * j) = v10;
        *(_DWORD *)(*(_DWORD *)(*((_DWORD *)self + 50) + 44 * i + 40) + 4 * j) = *((_DWORD *)self + 46)
                                                                               + 144
                                                                               * *(_DWORD *)(*(_DWORD *)(*((_DWORD *)self + 50) + 44 * i + 40)
                                                                                           + 4 * j);
      }
    }
    for ( i = 0; i < *((_DWORD *)self + 45); ++i )
    {
      *(_DWORD *)(*((_DWORD *)self + 46) + 144 * i + 132) = *((_DWORD *)self + 50)
                                                          + 44 * *(_DWORD *)(*((_DWORD *)self + 46) + 144 * i + 132);
      *(_DWORD *)(*((_DWORD *)self + 46) + 144 * i + 136) = *((_DWORD *)self + 50)
                                                          + 44 * *(_DWORD *)(*((_DWORD *)self + 46) + 144 * i + 136);
      *(_DWORD *)(*((_DWORD *)self + 46) + 144 * i + 140) = *((_DWORD *)self + 50)
                                                          + 44 * *(_DWORD *)(*((_DWORD *)self + 46) + 144 * i + 140);
    }
    *((_WORD *)self + 68) = (2 * rf_binary_stream_read_bool_versioned(stream, 196617, 0))
                          | *((_WORD *)self + 68) & 0xFFFD;
    *((_DWORD *)self + 51) = context[17] + 40 * context[16];
    context[16] += *((_DWORD *)self + 41);
    if ( (*((_DWORD *)self + 69) & 4) != 0 )
    {
      *((_DWORD *)self + 52) = operator new(6 * *((_DWORD *)self + 44) * *((_DWORD *)self + 41));
      for ( i = 0; i < *((_DWORD *)self + 41); ++i )
        *(_DWORD *)(*((_DWORD *)self + 51) + 40 * i + 4) = *((_DWORD *)self + 52) + 6 * *((_DWORD *)self + 44) * i;
      if ( !rf_binary_stream_version_at_least(stream, 196617) )
        context[20] += *((_DWORD *)self + 41);
    }
    else
    {
      *((_DWORD *)self + 52) = operator new(6 * *((_DWORD *)self + 44));
      *(_DWORD *)(*((_DWORD *)self + 51) + 4) = *((_DWORD *)self + 52);
      if ( ((*((_WORD *)self + 68) >> 1) & 1) != 0 )
      {
        if ( !rf_binary_stream_version_at_least(stream, 196622) )
          *((_DWORD *)self + 55) = context[21] + 40 * context[20]++;
        *((_DWORD *)self + 56) = context[23] + 20 * context[22]++;
      }
      else
      {
        *((_DWORD *)self + 55) = context[21] + 40 * context[20];
        context[20] += *((_DWORD *)self + 41);
      }
    }
    if ( rf_binary_stream_version_at_least(stream, 196621) )
    {
      if ( (*((_DWORD *)self + 69) & 0x100) != 0 )
        v36 = *((_DWORD *)self + 41);
      else
        v36 = 1;
      *((_DWORD *)self + 53) = context[19] + 4 * context[18];
      context[18] += v36;
      *((_DWORD *)self + 54) = operator new(24 * v36 * *((_DWORD *)self + 45));
      for ( i = 0; i < v36; ++i )
        *(_DWORD *)(*((_DWORD *)self + 53) + 4 * i) = *((_DWORD *)self + 54) + 24 * *((_DWORD *)self + 45) * i;
    }
    for ( i = 0; i < *((_DWORD *)self + 41); ++i )
    {
      if ( (*((_DWORD *)self + 69) & 4) != 0 || !i )
      {
        rf_binary_stream_read_vector3_versioned(stream, (float *)(*((_DWORD *)self + 51) + 40 * i + 8), 0, unk_1C8FBDC);
        rf_binary_stream_read_vector3_versioned(stream, (float *)(*((_DWORD *)self + 51) + 40 * i + 20), 0, unk_1C8FBDC);
        rf_binary_stream_read_int16_array(
          stream,
          *(__int16 **)(*((_DWORD *)self + 51) + 40 * i + 4),
          3 * *((_DWORD *)self + 44));
        if ( (*((_DWORD *)self + 69) & 0x801) != 0 )
        {
          v11 = rf_binary_stream_read_float_versioned(stream, 196619, v51);
          *(float *)(*((_DWORD *)self + 51) + 40 * i + 32) = v11;
          v12 = rf_binary_stream_read_float_versioned(stream, 196619, v52);
          *(float *)(*((_DWORD *)self + 51) + 40 * i + 36) = v12;
          if ( (*((_DWORD *)self + 69) & 0x800) != 0 && !i )
          {
            rf_binary_stream_read_vector3_versioned(stream, (float *)self + 70, 262145, unk_1C8FBDC);
            rf_vector_normalize((float *)self + 70);
          }
        }
      }
      if ( rf_binary_stream_version_at_least(stream, 196621) && ((*((_DWORD *)self + 69) & 0x100) != 0 || !i) )
      {
        for ( k = 0; k < *((_DWORD *)self + 45); ++k )
        {
          for ( j = 0; j < 3; ++j )
          {
            v13 = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
            *(float *)(*(_DWORD *)(*((_DWORD *)self + 53) + 4 * i) + 24 * k + 4 * j) = v13;
            v14 = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
            *(float *)(*(_DWORD *)(*((_DWORD *)self + 53) + 4 * i) + 24 * k + 4 * j + 12) = v14;
          }
        }
      }
      if ( (*((_DWORD *)self + 69) & 4) == 0
        && (((*((_WORD *)self + 68) >> 1) & 1) == 0 || !rf_binary_stream_version_at_least(stream, 196622) && !i) )
      {
        rf_binary_stream_read_vector3_versioned(stream, (float *)(*((_DWORD *)self + 55) + 40 * i), 0, unk_1C8FBDC);
        rf_binary_stream_read_float4_versioned(stream, (float *)(*((_DWORD *)self + 55) + 40 * i + 12), 0, unk_1C8FC3C);
        rf_binary_stream_read_vector3_versioned(stream, (float *)(*((_DWORD *)self + 55) + 40 * i + 28), 0, unk_1C8FBDC);
      }
      if ( !rf_binary_stream_version_at_least(stream, 196617) )
        rf_vfile_seek(stream, 1, 1);
      *(_DWORD *)(40 * i + *((_DWORD *)self + 51)) = *(_DWORD *)(*((_DWORD *)self + 51) + 40 * i) | 0x80000000;
      if ( !rf_binary_stream_version_at_least(stream, 262149) )
      {
        v34 = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
        v34 = rf_float_maximum_two_values(v34, 0.0);
        v34 = rf_float_minimum_two_values(v34, 1.0);
        for ( j = 0; j < *((_DWORD *)self + 47); ++j )
        {
          v33 = *(_DWORD *)(*((_DWORD *)self + 33) + 140) + 200 * *(_DWORD *)(*((_DWORD *)self + 48) + 4 * j);
          *(float *)(*(_DWORD *)(v33 + 196) + 4 * i) = v34;
        }
      }
    }
    if ( ((*((_WORD *)self + 68) >> 1) & 1) != 0 )
    {
      rf_binary_stream_read_vector3_versioned(stream, (float *)self + 57, 196618, flt_17F10B0);
      rf_binary_stream_read_float4_versioned(stream, (float *)self + 60, 196618, flt_18CD810);
      rf_vector3_set_components_return_destination(v31, 1.0, 1.0, 1.0);
      rf_binary_stream_read_vector3_versioned(stream, (float *)self + 64, 196618, v31);
      **((_WORD **)self + 56) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      if ( **((_WORD **)self + 56) )
      {
        *(_DWORD *)(*((_DWORD *)self + 56) + 8) = context[25] + 40 * context[24];
        context[24] += **((unsigned __int16 **)self + 56);
        for ( m = 0; m < **((unsigned __int16 **)self + 56); ++m )
        {
          v15 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
          *(_DWORD *)(40 * m + *(_DWORD *)(*((_DWORD *)self + 56) + 8)) = v15;
          rf_binary_stream_read_vector3_versioned(
            stream,
            (float *)(*(_DWORD *)(*((_DWORD *)self + 56) + 8) + 40 * m + 4),
            0,
            unk_1C8FBDC);
          rf_binary_stream_read_vector3_versioned(
            stream,
            (float *)(*(_DWORD *)(*((_DWORD *)self + 56) + 8) + 40 * m + 16),
            0,
            unk_1C8FBDC);
          rf_binary_stream_read_vector3_versioned(
            stream,
            (float *)(*(_DWORD *)(*((_DWORD *)self + 56) + 8) + 40 * m + 28),
            0,
            unk_1C8FBDC);
        }
      }
      *(_WORD *)(*((_DWORD *)self + 56) + 2) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      if ( *(_WORD *)(*((_DWORD *)self + 56) + 2) )
      {
        *(_DWORD *)(*((_DWORD *)self + 56) + 12) = context[27] + 20 * context[26];
        context[26] += *(unsigned __int16 *)(*((_DWORD *)self + 56) + 2);
        for ( m = 0; m < *(unsigned __int16 *)(*((_DWORD *)self + 56) + 2); ++m )
        {
          v16 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
          *(_DWORD *)(20 * m + *(_DWORD *)(*((_DWORD *)self + 56) + 12)) = v16;
          rf_float4_construct_zero_zero_zero_one(v30);
          rf_binary_stream_read_float4_versioned(stream, v30, 0, unk_1C8FC3C);
          *(_WORD *)(*(_DWORD *)(*((_DWORD *)self + 56) + 12) + 20 * m + 4) = (int)(v30[0] * 16383.0);
          *(_WORD *)(*(_DWORD *)(*((_DWORD *)self + 56) + 12) + 20 * m + 6) = (int)(v30[1] * 16383.0);
          *(_WORD *)(*(_DWORD *)(*((_DWORD *)self + 56) + 12) + 20 * m + 8) = (int)(v30[2] * 16383.0);
          *(_WORD *)(*(_DWORD *)(*((_DWORD *)self + 56) + 12) + 20 * m + 10) = (int)(v30[3] * 16383.0);
          v17 = (int)rf_binary_stream_read_float_versioned(stream, 0, 0.0);
          *(_BYTE *)(*(_DWORD *)(*((_DWORD *)self + 56) + 12) + 20 * m + 12) = v17;
          v18 = (int)rf_binary_stream_read_float_versioned(stream, 0, 0.0);
          *(_BYTE *)(*(_DWORD *)(*((_DWORD *)self + 56) + 12) + 20 * m + 13) = v18;
          v19 = (int)rf_binary_stream_read_float_versioned(stream, 0, 0.0);
          *(_BYTE *)(*(_DWORD *)(*((_DWORD *)self + 56) + 12) + 20 * m + 14) = v19;
          v20 = (int)rf_binary_stream_read_float_versioned(stream, 0, 0.0);
          *(_BYTE *)(*(_DWORD *)(*((_DWORD *)self + 56) + 12) + 20 * m + 15) = v20;
          v21 = (int)rf_binary_stream_read_float_versioned(stream, 0, 0.0);
          *(_BYTE *)(*(_DWORD *)(*((_DWORD *)self + 56) + 12) + 20 * m + 16) = v21;
        }
      }
      *(_WORD *)(*((_DWORD *)self + 56) + 4) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      if ( *(_WORD *)(*((_DWORD *)self + 56) + 4) )
      {
        *(_DWORD *)(*((_DWORD *)self + 56) + 16) = context[29] + 40 * context[28];
        context[28] += *(unsigned __int16 *)(*((_DWORD *)self + 56) + 4);
        for ( m = 0; m < *(unsigned __int16 *)(*((_DWORD *)self + 56) + 4); ++m )
        {
          v22 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
          *(_DWORD *)(40 * m + *(_DWORD *)(*((_DWORD *)self + 56) + 16)) = v22;
          rf_binary_stream_read_vector3_versioned(
            stream,
            (float *)(*(_DWORD *)(*((_DWORD *)self + 56) + 16) + 40 * m + 4),
            0,
            unk_1C8FBDC);
          rf_binary_stream_read_vector3_versioned(
            stream,
            (float *)(*(_DWORD *)(*((_DWORD *)self + 56) + 16) + 40 * m + 16),
            0,
            unk_1C8FBDC);
          rf_binary_stream_read_vector3_versioned(
            stream,
            (float *)(*(_DWORD *)(*((_DWORD *)self + 56) + 16) + 40 * m + 28),
            0,
            unk_1C8FBDC);
        }
      }
    }
    *((_DWORD *)self + 35) = 0;
  }
}

