package br.univali.cc.behavior;

import jade.core.Agent;
import jade.core.behaviours.Behaviour;

public class MyBehavior extends Behaviour {
    public MyBehavior(Agent agent) { super(agent); }

    private int count = 0;
    public void action() {
        System.out.println("- Hello world, my name is " + myAgent.getLocalName()); count++;
    }

    public boolean done() { return count > 2; }
}
