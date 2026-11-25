Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class WinList {
  public delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumWindowsProc lpEnumFunc, IntPtr lParam);
  [DllImport("user32.dll", CharSet = CharSet.Auto)] public static extern int GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr hWnd);
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint lpdwProcessId);
  [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr hWnd);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);

  public static void List() {
    EnumWindows((hWnd, lParam) => {
      if (!IsWindowVisible(hWnd)) return true;
      StringBuilder sb = new StringBuilder(256);
      GetWindowText(hWnd, sb, 256);
      string title = sb.ToString();
      if (string.IsNullOrWhiteSpace(title)) return true;
      uint pid = 0;
      GetWindowThreadProcessId(hWnd, out pid);
      bool iconic = IsIconic(hWnd);
      Console.WriteLine(string.Format("HWND: 0x{0:X8} PID: {1,6} Iconic: {2,-5} Title: {3}", hWnd.ToInt64(), pid, iconic, title));
      return true;
    }, IntPtr.Zero);
  }
}
"@
[WinList]::List()
