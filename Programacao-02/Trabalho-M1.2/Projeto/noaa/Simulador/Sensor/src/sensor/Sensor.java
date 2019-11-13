/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sensor;

/**
 *
 * @author efraim
 */
public class Sensor
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception
    {
        while(true) {
            double data = Math.random();
            System.out.println(data);
            Thread.sleep(2000);
        }
        
    }
    
}
