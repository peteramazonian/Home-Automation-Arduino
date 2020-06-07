package sample;

import com.jfoenix.controls.JFXToggleButton;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Platform;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.util.Duration;
import jssc.SerialPort;

import java.util.Iterator;
import java.util.LinkedHashSet;

public class Controller  {
    public VBox car;
    public VBox zen;
    public JFXToggleButton light1;
    public JFXToggleButton light2;
    public JFXToggleButton bed;
    public Label val;
    String buffer,Current;

    LinkedHashSet<String> queue = new LinkedHashSet<>();

    boolean flag = false;
    boolean TFlag = false;

    private void incrementCount() {
        if (!queue.isEmpty()){
            Iterator<String > itr=queue.iterator();
            String temp = itr.next();
            switch (temp){
                    //Temp ->
                    case "15": case "16": case "17": case "18": case "19":
                    case "20": case "21": case "22": case "23": case "24": case "25":
                    case "26": case "27": case "28": case "29":
                    case "30": case "31": case "32": case "33": case "34": case "35":
                        TFlag=true;
                        buffer=Current;
                        break;
                    //case "43":
                    case "10":
                        //System.out.println("Bed OFF");
                        bed.setSelected(false);
                        break;
                    case "11":
                        //System.out.println("Bed ON");
                        bed.setSelected(true);
                        break;
                    case "44":
                        //System.out.println("Light1&2 OFF");
                        light1.setSelected(false);
                        light2.setSelected(false);
                        break;
                    case "45":
                        //System.out.println("Light1 ON-2 OFF");
                        light1.setSelected(true);
                        light2.setSelected(false);
                        break;
                    case "54":
                        //System.out.println("Light1 OFF-2 ON");
                        light1.setSelected(false);
                        light2.setSelected(true);
                        break;
                    case "55":
                        //System.out.println("Light1&2 ON");
                        light1.setSelected(true);
                        light2.setSelected(true);
                        break;
                    case "50":
                        //System.out.println("Zen OFF");
                        zen.setVisible(false);
                        break;
                    case "51":
                        //System.out.println("Zen ON");
                        zen.setVisible(true);
                        break;
                    case "61":
                        //System.out.println("Car ON");
                        Timeline flasher = new Timeline(
                                new KeyFrame(Duration.seconds(0.5), e -> car.setVisible(true)),
                                new KeyFrame(Duration.seconds(1.0), e -> car.setVisible(false))
                        );
                        flasher.setCycleCount(5);
                        flasher.play();
                    default:
                        System.out.println("is Not Supported");
                        break;
                }
                queue.remove(temp);

            }
        if (TFlag){
            val.setText(buffer);
            TFlag = false;
        }
    }

    public void initialize(){
        //initializing Car and Zen Mode -> to be unvisible at first
        car.setVisible(false);
        zen.setVisible(false);


        SerialPort serialPort = new SerialPort("COM3");
        try {
            serialPort.openPort();//Open serial port
            serialPort.setParams(9600, 8, 1, 0);//Set params.
        }catch (Exception ignored){}
        Thread thread = new Thread(new Runnable() {

            @Override
            public void run() {
                Runnable updater = new Runnable() {

                    @Override
                    public void run() {
                        incrementCount();
                    }
                };

                while (true) {
                    try {
                        Current = serialPort.readString(2);
                        if (!Current.contains("\n")){
                            queue.add(Current);
                            System.out.println(Current);
                            System.out.println(queue.size());
                        }
                    } catch (Exception ignored){}

                    Platform.runLater(updater);
                }
            }

        });
        thread.setDaemon(true);
        thread.start();

    }

}