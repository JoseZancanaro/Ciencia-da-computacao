package br.univali.cc.behavior;

import jade.core.Agent;

/*  Program arguments
    -agents
    Ze:br.univali.cc.behavior.MyAgent
*/
public class MyAgent extends Agent {
    protected void setup() {
        System.out.println("Hello, i am a Agent!");
        System.out.println("I'm shooting my behaviors...");
        this.addBehaviour(new MyBehavior(this));
    }
}
