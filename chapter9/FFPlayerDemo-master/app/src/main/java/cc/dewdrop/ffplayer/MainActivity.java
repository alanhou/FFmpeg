package cc.dewdrop.ffplayer;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import cc.dewdrop.ffplayer.utils.FFUtils;
import cc.dewdrop.ffplayer.widget.FFVideoView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    private TextView mTextView;
    private FFVideoView mVideoView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mTextView = findViewById(R.id.sample_text);
        mVideoView = findViewById(R.id.videoView);
    }

    public void onButtonClick(View view) {
        int id = view.getId();

        switch (id) {
            /*
            case R.id.button_protocol:
                setInfoText(FFUtils.urlProtocolInfo());
                break;
            case R.id.button_codec:
                setInfoText(FFUtils.avCodecInfo());
                break;
            case R.id.button_filter:
                setInfoText(FFUtils.avFilterInfo());
                break;
            case R.id.button_format:
                setInfoText(FFUtils.avFormatInfo());
                break;
                */
            case R.id.button_play:
                //String videoPath = Environment.getExternalStorageDirectory() + "/Movies/PERU.MP4";
                String videoPath = Environment.getExternalStorageDirectory() + "/DCIM/Camera/VID_20160527_153309.mp4";

                mVideoView.playVideo(videoPath);
                break;
        }
    }

    private void setInfoText(String content) {
        if (mTextView != null) {
            mTextView.setText(content);
        }
    }
}
