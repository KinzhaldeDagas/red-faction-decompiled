// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518D30 sub_518D30
// UNREALRED VERIFIED [combat-panic-20261104]: Prepare nodeworking positions/eligibility518210 then chooseanchor518640(config,0). Uniform rand modulo(nonblocked anchorneighbors+1), preserving native adjacency order. Extra lastchoice yields2nodes[start,end], otherwise4[start,anchor,neighbor,end].518F60 samples endpoint within chosen node; links synthetic end to chosen node; copies workingendpoint to its base at518F4A. No away-from-attacker vector or area-uniform disk sampling.
char __thiscall sub_518D30(_DWORD *this, _DWORD *request)
{
  float copy_result[3]; // [esp+4h] [ebp-20h] BYREF
  int v5; // [esp+10h] [ebp-14h]
  int v6; // [esp+14h] [ebp-10h]
  float *v7; // [esp+18h] [ebp-Ch]
  int i; // [esp+1Ch] [ebp-8h]
  int v9; // [esp+20h] [ebp-4h]

  request[13] = 0;
  rf_pointer_array_clear_count_keep_storage((_DWORD *)(*request + 40));
  rf_nav_graph_prepare_request_nodes(this, (int)request);
  if ( !rf_nav_graph_connect_start_node(this, request, nullptr) )
    return 0;
  v6 = 1;
  v7 = *(float **)sub_552200((_DWORD *)(*request + 40), 0);
  for ( i = 0; i < rf_receiver_get_first_dword(v7 + 10); ++i )
  {
    if ( !*(_BYTE *)(*(_DWORD *)sub_552200((_DWORD *)v7 + 10, i) + 53) )
      ++v6;
  }
  v9 = rand() % v6;
  rf_pointer_array_clear_count_keep_storage((_DWORD *)(request[3] + 40));
  if ( v9 == v6 - 1 )
  {
    sub_518F60((int)request, v7, (float *)(request[3] + 12));
    request[13] = 2;
    *(_DWORD *)request[14] = *request;
    *(_DWORD *)(request[14] + 4) = request[3];
    rf_pointer_array_append_dword((_DWORD *)(request[3] + 40), (int)v7);
  }
  else
  {
    v5 = 0;
    for ( i = 0; i < rf_receiver_get_first_dword(v7 + 10); ++i )
    {
      if ( !*(_BYTE *)(*(_DWORD *)sub_552200((_DWORD *)v7 + 10, i) + 53) )
      {
        if ( v9 == v5 )
        {
          request[4] = *(_DWORD *)sub_552200((_DWORD *)v7 + 10, i);
          break;
        }
        ++v5;
      }
    }
    sub_518F60((int)request, (float *)request[4], (float *)(request[3] + 12));
    rf_pointer_array_append_dword((_DWORD *)(request[3] + 40), request[4]);
    request[13] = 4;
    *(_DWORD *)request[14] = *request;
    *(_DWORD *)(request[14] + 4) = v7;
    *(_DWORD *)(request[14] + 8) = request[4];
    *(_DWORD *)(request[14] + 12) = request[3];
  }
  rf_vector_copy((float *)request[3], copy_result, (const float *)(request[3] + 12));
  return 1;
}

