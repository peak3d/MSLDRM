package com.peak3d.msldrm;

import android.media.NotProvisionedException;
import android.media.ResourceBusyException;
import android.media.UnsupportedSchemeException;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.media.MediaDrm;

import java.util.Arrays;
import java.util.UUID;
import java.lang.String;

public class MainActivity extends AppCompatActivity {

    public static final UUID WIDEVINE_UUID = new UUID(0xEDEF8BA979D64ACEL, 0xA3C827DCD51D21EDL);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        String hello = new String();
        byte[] session;
        byte[] keySetId = "ksid1F0269A6".getBytes();
        byte[] keyId = "1523566848782".getBytes();
        byte[] hmacKeyId = "1523569990375".getBytes();
        byte[] data = "1111111111111111".getBytes();
        byte[] iv = "1234567812345678".getBytes();

         try {
             MediaDrm mediaDrm = new MediaDrm(WIDEVINE_UUID);

             try {
                 session = mediaDrm.openSession();
                 hello += "SessionId" + Arrays.toString(session) + "\n";

                 MediaDrm.CryptoSession cryptoSession = mediaDrm.getCryptoSession(session, "AES/CBC/NoPadding", "HmacSHA256");

                 mediaDrm.restoreKeys(session, keySetId);

                 byte[] encrypted = cryptoSession.encrypt(keyId, data, iv);

                 hello += "Encrypted: " + Arrays.toString(encrypted) + "\n";

                 byte[] signature = cryptoSession.sign(hmacKeyId, encrypted);

                 hello += "Signature: " + Arrays.toString(signature) + "\n";

                 mediaDrm.removeKeys(session);

                 mediaDrm.closeSession(session);

                 mediaDrm.release();


             } catch (NotProvisionedException e) {

             } catch (ResourceBusyException e){
             }
         } catch (UnsupportedSchemeException e){}



        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);


        //tv.setText(stringFromJNI());
        tv.setText(hello);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
}
