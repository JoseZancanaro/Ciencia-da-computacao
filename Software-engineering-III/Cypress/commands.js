Cypress.Commands.add("removeAllTasks", () => { 
    cy.get("ul#mytodos").children().each(() => {
        cy.get("ul#mytodos").children().first().find(".delete").click({force: true})
    }
})