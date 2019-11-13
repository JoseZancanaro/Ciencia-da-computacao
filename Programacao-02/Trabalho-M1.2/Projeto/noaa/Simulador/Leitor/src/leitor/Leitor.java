/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package leitor;

import java.io.IOException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author efraim
 */
public class Leitor
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        // TODO code application logic here
        Runtime runtime = Runtime.getRuntime();
        Process process;
        try {
            //process = runtime.exec("java -jar \"/home/efraim/Documents/Sensor/dist/Sensor.jar\"");
            process = runtime.exec("ping www.univali.br");
            //Thread.sleep(5000);
            Scanner scanner = new Scanner(process.getInputStream());
            while (true) {
                System.out.println(scanner.nextLine());
            }
        } catch (Exception ex) {
           ex.printStackTrace();
        }

    }

}
