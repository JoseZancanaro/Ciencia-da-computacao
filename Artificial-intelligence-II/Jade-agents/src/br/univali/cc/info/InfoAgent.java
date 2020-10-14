package br.univali.cc.info;

import jade.core.Agent;
import java.util.Iterator;

/*  Program arguments
    -agents
    InfoAgent:br.univali.cc.info.InfoAgent
*/
public class InfoAgent extends Agent {
    protected void setup() {
        // Can replace 'this' with 'getAID()'
        System.out.println("Hello, i am a Agent!");
        System.out.println("+ All my informations below: \n" + this.getAID());
        System.out.println("+ My local name is " + this.getLocalName());
        System.out.println("+ My global name is " + this.getName());
        System.out.println("+ My addresses are: ");

        Iterator it = getAID().getAllAddresses();
        while (it.hasNext()) {
            System.out.println("    - " + it.next());
        }
    }
}
