package cc.dewdrop.ffplayer.utils;

import android.os.Build;
import android.view.Surface;

/**
 * Created by Zhang Tingkuo.
 * Date: 2017-07-21
 * Time: 15:26
 */

public class FFUtils {



    public static native String urlProtocolInfo();

    public static native String avFormatInfo();

    public static native String avCodecInfo();

    public static native String avFilterInfo();

    public static native void playVideo(String videoPath, Surface surface);
}
