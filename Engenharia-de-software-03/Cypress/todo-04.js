describe("Fourth automated test", function() {
    it("Remove all tasks, add new ones and checks order", function() {
        cy.visit("https://todolistme.net/")

        // Remove all tasks
        cy.get("ul#mytodos").children().each(() => {
            cy.get("ul#mytodos").children().first().each((children) => {
                cy.get(children).find(".delete").click({force: true}).as("task-removed")
            })
        })

        cy.wait(500)

        let tasks = [ "Limpar a casa.", 
                      "Fazer um belo bolo.", 
                      "Elaborar códigos legíveis.",
                      "Jogar um bom game." ]

        // Add new tasks
        tasks.forEach(task => {
            cy.get("#additempanel").type(task).type("{enter}").as("task-added")
        })
        
        cy.wait(500)
        
        // Check ordering methods
        cy.get("#sortselect").get("#sort0").click().as("sort-normal")
        cy.wait(500)

        cy.get("#sortselect").get("#sort1").click().as("sort-alphabetical")
        cy.wait(500)

        let max = 3
        for (let i = 0; i < max; i++) {
            cy.get("#sortselect").get("#sort2").click().as("sort-random")
            cy.wait(500)
        }

        cy.get("#sortselect").get("#sort3").click().as("sort-top-3")
        cy.wait(500)
    })
})