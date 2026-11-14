// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00515070 rf_benchmark_panel_dispatch
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, timedemo/framerate state machine,x87FPS extrema,log ABI and recovered console handlers,original ECX/stack flow and PE bytes): Cdecl integer panel,caller pops4,void. Handles5/11/22,otherwise delegates4F11E0(panel,0). Panel5 calls447BE0;on NULLworld resets keyboard/mouse,prints specified-level error,requestsmenu2 without clearing benchmarkstatus here. On worldsuccess call505D30(actual body writes90B508=1 despite false ___setargv label),then40CD80(stops active player firing,zeros player336 vector,sets6663D1=1);ifnavModeBYTE92DE10 nonzero snapshot world nav-array768 count into92DE18. Panel11 FIRST updates/draws frame via5155F0,then resolve entity from local-player+20 (local-player pointer itself unguarded). Missing entity requestsresults22 before sampling. Otherwise store
// entityFLOAT1828=F32(signedstep92DDFC*double0.01745329238474369),call4D7E90,then sample FPS=F32(1/frameDeltaSeconds),NO zero/finite guard. Minimum tracking: update currentMin663AE8 when(old>FPS ORold==0) AND FPS!=4,then apply SAME test to globalMin92DE14 ONLY if current minimum updated. Maximum tracking similarly updatescurrentMax92DE0C thennested globalMax92DDF4 when(old<FPS ORold==0),WITHOUT4FPS exclusion. Rawx87 comparisons verified in2048 finite/zero/infinity/NaN cases:zero sentinels admitNaN;NaN extrema are sticky onlater finite samples. Always F32-add FPS to92DE08,including4FPS andNaN;add signed integerstep to32-bit rotationDegrees92DE20. Only after signedcounter>=360 complete batch. Timedemo mode requests22. Navigation mode computes F32batchmean=FPSsum/(360.0/step),F32-adds it tosumOfNavMeans;prints/logs navIndex,currentMin/currentMax;resets rotation/sum/currentMax
// to0,currentMin=10000,++completedNavCount. This is fixed expected-sample denominator,NOT frames/elapsed-time FPS. Increment navIndex AT LEASTONCE;skip later entries while signedindex<count AND (recordFLOAT32<2 OR recordFLOAT28<0.5);unorderedNaN dimensions do NOT cause skip. First batch samples CURRENT player position labeledindex0 without validating/teleporting to node0,even if navCount0. For admitted later index copy recordXYZ0 and set entity position4BC330. If index exhausted copy global extrema into current extrema,store sumOfNavMeans/completedNavCount intoFPSsum,request22. Panel22 average is sumOfNavMeans/completedNavCount fornavmode,otherwiseFPSsum/(360.0/step),with no samplecount/step division guards. Print/log level-name92DD90 andglobal extrema;formatted buffer is passed as printf FORMAT itself. Setstatus92DE1C=0,clear6663D1 via40CDE0,clear90B508
// via505D20,preparemenu/resetinput,request2. If command-line state663AF0==3 invoke matching5157C0/515930(NULL),whose state3 exits1. No real-time rotation duration,initial waypoint qualification,invalid-step prevention or forcedpanel request success check.
void __cdecl rf_benchmark_panel_dispatch(int a1)
{
  float **v1; // eax
  float v2[3]; // [esp+1Ch] [ebp-ECh] BYREF
  char Buffer[204]; // [esp+28h] [ebp-E0h] BYREF
  float v4; // [esp+F8h] [ebp-10h]
  float v5; // [esp+FCh] [ebp-Ch]
  int v6; // [esp+100h] [ebp-8h]
  float v7; // [esp+104h] [ebp-4h]

  v6 = 0;
  switch ( a1 )
  {
    case 5:
      rf_ui_execute_level_load_transition();
      if ( rf_world_solid )
      {
        rf_trigger_set_global_activation_suppression();
        rf_ai_pause_updates_and_stop_entity_firing();
        if ( byte_92DE10 )
          dword_92DE18 = rf_receiver_get_first_dword((void *)(rf_world_solid + 768));
      }
      else
      {
        rf_input_reset_all_key_and_event_state();
        rf_mouse_reset_buttons_and_motion();
        rf_console_output_append_text_lines("\nERROR: specified level does not exist", nullptr);
        rf_ui_request_panel_immediate(2, 0);
      }
      break;
    case 11:
      rf_benchmark_update_and_render_frame();
      v6 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_fpgun_player + 20));
      if ( v6 )
      {
        *(float *)(v6 + 1828) = (double)dword_92DDFC * 0.01745329238474369;
        rf_entity_predict_motion_by_current_descriptor(v6);
        v5 = 1.0 / rf_frame_delta_seconds;
        if ( flt_663AE8 > (double)v5 && v5 != 4.0 || flt_663AE8 == 0.0 && v5 != 4.0 )
        {
          if ( (flt_663AE8 = v5, unk_92DE14 > (double)v5) && v5 != 4.0 || unk_92DE14 == 0.0 && v5 != 4.0 )
            unk_92DE14 = v5;
        }
        if ( unk_92DE0C < (double)v5 || unk_92DE0C == 0.0 )
        {
          unk_92DE0C = v5;
          if ( unk_92DDF4 < (double)v5 || unk_92DDF4 == 0.0 )
            unk_92DDF4 = v5;
        }
        unk_92DE08 = unk_92DE08 + v5;
        dword_92DE20 += dword_92DDFC;
        if ( dword_92DE20 >= 360 )
        {
          if ( byte_92DE10 )
          {
            if ( !dword_92DDF8 )
            {
              rf_console_output_append_text_lines("\n[Framerate Test]\n", nullptr);
              printf("\n[Framerate Test]\n");
            }
            v7 = unk_92DE08 / (360.0 / (double)dword_92DDFC);
            unk_92DE00 = unk_92DE00 + v7;
            sprintf(
              Buffer,
              "Nav point: %d   Average frames per second: %.2f   min: %.2f   max: %.2f",
              dword_92DDF8,
              v7,
              flt_663AE8,
              unk_92DE0C);
            rf_console_output_append_text_lines(Buffer, nullptr);
            printf(Buffer);
            rf_benchmark_write_timedemo_log(Buffer);
            dword_92DE20 = 0;
            unk_92DE08 = 0.0;
            unk_92DE0C = 0.0;
            flt_663AE8 = 10000.0;
            ++dword_92DE04;
            do
              ++dword_92DDF8;
            while ( dword_92DDF8 < dword_92DE18
                 && (*(float *)(*(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), dword_92DDF8) + 32) < 2.0
                  || *(float *)(*(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), dword_92DDF8) + 28) < 0.5) );
            if ( dword_92DDF8 >= dword_92DE18 )
            {
              flt_663AE8 = unk_92DE14;
              unk_92DE0C = unk_92DDF4;
              unk_92DE08 = unk_92DE00 / (double)dword_92DE04;
              rf_ui_request_panel_immediate(22, 0);
            }
            else
            {
              v1 = (float **)sub_552200((_DWORD *)(rf_world_solid + 768), dword_92DDF8);
              rf_vector3_copy_return_destination(v2, *v1);
              rf_object_publish_position_and_bounds(v6, v2);
            }
          }
          else
          {
            rf_ui_request_panel_immediate(22, 0);
          }
        }
      }
      else
      {
        rf_ui_request_panel_immediate(22, 0);
      }
      break;
    case 22:
      if ( byte_92DE10 )
      {
        rf_console_output_append_text_lines("\n[Overall results]\n", nullptr);
        printf("\n[Overall results]\n");
        v4 = unk_92DE00 / (double)dword_92DE04;
      }
      else
      {
        rf_console_output_append_text_lines("\n[Timedemo]\n", nullptr);
        printf("\n[Timedemo]\n");
        v4 = unk_92DE08 / (360.0 / (double)dword_92DDFC);
      }
      sprintf(
        Buffer,
        "Level: %s   Average frames per second: %.2f   min: %.2f   max: %.2f\n\n",
        unk_92DD90,
        v4,
        unk_92DE14,
        unk_92DDF4);
      rf_console_output_append_text_lines(Buffer, nullptr);
      printf(Buffer);
      rf_benchmark_write_timedemo_log(Buffer);
      unk_92DE1C = 0;
      rf_ai_resume_updates();
      rf_trigger_clear_global_activation_suppression();
      rf_prepare_multiplayer_menu_without_session();
      rf_input_reset_all_key_and_event_state();
      rf_mouse_reset_buttons_and_motion();
      rf_ui_request_panel_immediate(2, 0);
      if ( dword_663AF0 == 3 )
      {
        if ( byte_92DE10 )
          rf_framerate_test_command_line_state_step(nullptr);
        else
          rf_timedemo_command_line_state_step(nullptr);
      }
      break;
    default:
      rf_ui_dispatch_panel_frame(a1, 0);
      break;
  }
}

