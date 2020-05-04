describe("Third automated test", function() {
    it("Add new list, new tasks and completed them", function() {
        cy.visit("https://todolistme.net/")

        // Add a new list
        let listName = "Minha nova lista"
        cy.get("#addlist").click()
        cy.get("#updatebox").type(listName).type("{enter}").as("list-created")
        
        let tasks = ["Levar o lixo para fora.", 
                     "Elaborar o desafio do cypress." ]

        
        // Add new tasks
        tasks.forEach(task => {
            cy.get("#additempanel").type(task).type("{enter}").as("task-added")
        })
        
        // Mark tasks as completed
        cy.get("ul#mytodos").children().each(() => {
            cy.get("[type='checkbox']").check().as("task-checked")
        })
    })
})