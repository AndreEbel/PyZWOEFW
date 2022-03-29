using System;
using System.Runtime.InteropServices;
using System.Text;

namespace ZWOptical.EFWSDK
{
    public class EFWdll
    {
        public enum EFW_ERROR_CODE
        {
            EFW_SUCCESS = 0,
	        EFW_ERROR_INVALID_INDEX,
	        EFW_ERROR_INVALID_ID,
	        EFW_ERROR_INVALID_VALUE,
	        EFW_ERROR_REMOVED, 
	        EFW_ERROR_MOVING,
	        EFW_ERROR_ERROR_STATE,
	        EFW_ERROR_GENERAL_ERROR,//other error
	        EFW_ERROR_END = -1
        }

     	[StructLayout(LayoutKind.Sequential)]
        public struct EFW_INFO
        {
            public int ID;
            [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.U1, SizeConst = 64)]
            public byte[] name;
            public int slotNum;
            
            public string Name
            {
                get { return Encoding.ASCII.GetString(name).TrimEnd((Char)0); }
            }
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct EFW_ID
        {
            [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.U1, SizeConst = 8)]
            public byte[] id;
        }
       

        [DllImport("EFW_filter_ASCOM.dll", EntryPoint = "EFWGetNum", CallingConvention = CallingConvention.Cdecl)]
        private static extern int EFWGetNum32();

        [DllImport("EFW_filter_ASCOM.dll", EntryPoint = "EFWGetID", CallingConvention = CallingConvention.Cdecl)]
        private static extern EFW_ERROR_CODE EFWGetID32(int index, out int ID);

        [DllImport("EFW_filter_ASCOM.dll", EntryPoint = "EFWGetProperty", CallingConvention = CallingConvention.Cdecl)]
        private static extern EFW_ERROR_CODE EFWGetProperty32(int ID, out EFW_INFO pInfo);

        [DllImport("EFW_filter_ASCOM.dll", EntryPoint = "EFWOpen", CallingConvention = CallingConvention.Cdecl)]
        private static extern EFW_ERROR_CODE EFWOpen32(int index);


        [DllImport("EFW_filter_ASCOM.dll", EntryPoint = "EFWClose", CallingConvention = CallingConvention.Cdecl)]
        private static extern EFW_ERROR_CODE EFWClose32(int ID);
      

        [DllImport("EFW_filter_ASCOM.dll", EntryPoint = "EFWGetPosition", CallingConvention = CallingConvention.Cdecl)]
        private static extern EFW_ERROR_CODE EFWGetPosition32(int ID, out int pPosition);
      

        [DllImport("EFW_filter_ASCOM.dll", EntryPoint = "EFWSetPosition", CallingConvention = CallingConvention.Cdecl)]
        private static extern EFW_ERROR_CODE EFWSetPosition32(int ID, int Position);

        [DllImport("EFW_filter_ASCOM.dll", EntryPoint = "EFWSetDirection", CallingConvention = CallingConvention.Cdecl)]
        private static extern EFW_ERROR_CODE EFWSetDirection32(int ID, [MarshalAs(UnmanagedType.I1)]bool bUnidirectional);

      
        [DllImport("EFW_filter_ASCOM.dll", EntryPoint = "EFWGetDirection", CallingConvention = CallingConvention.Cdecl)]
        private static extern EFW_ERROR_CODE EFWGetDirection32(int ID, [MarshalAs(UnmanagedType.I1)]out bool bUnidirectional);

        [DllImport("EFW_filter_ASCOM.dll", EntryPoint = "EFWGetFirmwareVersion", CallingConvention = CallingConvention.Cdecl)]
        private static extern EFW_ERROR_CODE EFWGetFWVer32(int ID, out byte pbMajor, out byte pbMinor, out byte pbBuild);

        [DllImport("EFW_filter_ASCOM.dll", EntryPoint = "EFWGetSerialNumber", CallingConvention = CallingConvention.Cdecl)]
        private static extern EFW_ERROR_CODE EFWGetSerialNumber32(int ID, out EFW_ID sn);

        [DllImport("EFW_filter_ASCOM.dll", EntryPoint = "EFWSetID", CallingConvention = CallingConvention.Cdecl)]
        private static extern EFW_ERROR_CODE EFWSetID32(int ID, EFW_ID alias);

        public static int GetNum() { return EFWGetNum32(); }
      
        public static EFW_ERROR_CODE GetID(int index, out int ID){ return  EFWGetID32(index, out ID); }

        public static EFW_ERROR_CODE GetProperty(int ID, out EFW_INFO pInfo){ return  EFWGetProperty32( ID, out pInfo); }

        public static EFW_ERROR_CODE Open(int index){ return EFWOpen32(index) ; }

        public static EFW_ERROR_CODE Close(int ID){ return EFWClose32(ID); }

        public static EFW_ERROR_CODE GetPosition(int ID, out int pPosition){ return  EFWGetPosition32(ID, out pPosition); }

        public static EFW_ERROR_CODE SetPosition(int ID, int Position){ return EFWSetPosition32(ID, Position); }

        public static EFW_ERROR_CODE GetDirection(int ID, out bool bUnidirectional){ return  EFWGetDirection32(ID, out bUnidirectional); }

        public static EFW_ERROR_CODE SetDirection(int ID, bool bUnidirectional){ return  EFWSetDirection32(ID, bUnidirectional); }

        public static EFW_ERROR_CODE GetFWVer(int ID, out byte bMajor, out byte bMinor, out byte bBuild){ return EFWGetFWVer32(ID, out bMajor, out bMinor, out bBuild); }

        public static EFW_ERROR_CODE GetSerialNumber(int ID, out EFW_ID sn){ return EFWGetSerialNumber32(ID, out sn); }

        public static EFW_ERROR_CODE SetID(int ID, EFW_ID alias){ return EFWSetID32(ID, alias); }
    }


}
