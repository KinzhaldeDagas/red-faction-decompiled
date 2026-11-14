// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600100 rf_jpeg_jinit_compress_master
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcinit.c:jinit_compress_master matched): Initializesmastercontrol0x604A20(cinfo,FALSE). Ifraw_data_in172==0,initializescolorconverter604020,downsampler603330,prepcontroller602B90(FALSE). InitializesforwardDCT6025D0. Arithmetic176 ->fatal1 ArithNotImpl;elseprogressive224 ->fatal48 NotCompiled;otherwiseHuffmanencoder6017A0. Coefcontroller600670 getsfullbuffer TRUE iffnum_scans164>1 ORoptimize_coding180;maincontroller600410(FALSE),markerwriter5FF3E0;memory.realize_virt_arrays+24;marker.write_file_header+0(SOI/optionalAPPs)immediately. Frame/scanheadersdelayed toallowapplicationmarkers. ThisRFbuildsupportssequentialHuffmancompression,multipasscoefficientbufferbutnotprogressive/arithmeticencoding.
int __cdecl rf_jpeg_jinit_compress_master(_DWORD *cinfo)
{
  rf_jpeg_jinit_c_master_control(cinfo, 0);
  if ( !cinfo[43] )
  {
    rf_jpeg_jinit_color_converter((int)cinfo);
    rf_jpeg_jinit_downsampler(cinfo);
    rf_jpeg_jinit_c_prep_controller((int)cinfo, 0);
  }
  rf_jpeg_jinit_forward_dct(cinfo);
  if ( cinfo[44] )
  {
    *(_DWORD *)(*cinfo + 20) = 1;
    (*(void (__cdecl **)(_DWORD *))*cinfo)(cinfo);
  }
  else if ( cinfo[56] )
  {
    *(_DWORD *)(*cinfo + 20) = 48;
    (*(void (__cdecl **)(_DWORD *))*cinfo)(cinfo);
  }
  else
  {
    rf_jpeg_jinit_huff_encoder((int)cinfo);
  }
  if ( (int)cinfo[41] > 1 || cinfo[45] )
    rf_jpeg_jinit_c_coef_controller((int)cinfo, 1);
  else
    rf_jpeg_jinit_c_coef_controller((int)cinfo, 0);
  rf_jpeg_jinit_c_main_controller(cinfo, 0);
  rf_jpeg_jinit_marker_writer((int)cinfo);
  (*(void (__cdecl **)(_DWORD *))(cinfo[1] + 24))(cinfo);
  return (*(int (__cdecl **)(_DWORD *))cinfo[86])(cinfo);
}

