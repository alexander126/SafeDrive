package com.example.cyrenians.safedrivingapp;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class Main2Activity extends AppCompatActivity implements LocationListener {

    RelativeLayout RL;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        RL = (RelativeLayout)findViewById(R.id.layout);

        LocationManager manager = (LocationManager) this.getSystemService(Context.LOCATION_SERVICE);

        this.onLocationChanged(null);

    }

    @Override
    public void onLocationChanged(Location location) {
        TextView txt = (TextView) findViewById(R.id.speed);
        if(location == null){
            txt.setText("0.0 m/s");

        }else {
            float nCurrentSpeed = location.getSpeed();
            txt.setText(nCurrentSpeed + " m/s");
            if(nCurrentSpeed > 50){
                RL.setBackgroundColor(Color.parseColor("#ff0000"));
            }
        }

    }

    @Override
    public void onStatusChanged(String s, int i, Bundle bundle) {

    }

    @Override
    public void onProviderEnabled(String s) {

    }

    @Override
    public void onProviderDisabled(String s) {

    }
}
