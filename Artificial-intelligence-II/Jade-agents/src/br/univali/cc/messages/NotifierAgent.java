package br.univali.cc.messages;

import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.OneShotBehaviour;
import jade.lang.acl.ACLMessage;

/*  Program arguments
    -agents
    Worker:br.univali.cc.messages.WorkerAgent;Notifier:br.univali.cc.messages.NotifierAgent
*/
public class NotifierAgent extends Agent {
    protected void setup() {
        this.addBehaviour(new OneShotBehaviour(this) {
            @Override
            public void action() {
                ACLMessage msg = new ACLMessage(ACLMessage.INFORM);
                msg.addReceiver(new AID("Worker", AID.ISLOCALNAME));
                msg.setLanguage("Portuguese");
                msg.setOntology("Emergency");
                msg.setContent("Work");

                myAgent.send(msg);
            }
        });
    }
}
