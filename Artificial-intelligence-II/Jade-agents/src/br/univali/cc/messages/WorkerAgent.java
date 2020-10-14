package br.univali.cc.messages;

import jade.core.Agent;
import jade.core.behaviours.CyclicBehaviour;
import jade.lang.acl.ACLMessage;

/*  Program arguments
    -agents
    Worker:br.univali.cc.messages.WorkerAgent;Notifier:br.univali.cc.messages.NotifierAgent
*/
public class WorkerAgent extends Agent {
    protected void setup() {
        this.addBehaviour(new CyclicBehaviour(this) {
            @Override
            public void action() {
                ACLMessage msg = myAgent.receive();
                if (msg != null) {
                    String content = msg.getContent();
                    if (content.equalsIgnoreCase("Work")) {
                        System.out.println("The Agent " + msg.getSender().getName() + " warned of a job");
                        System.out.println("I will activate the procedures");
                    }
                } else { block(); }
            }
        });
    }
}
