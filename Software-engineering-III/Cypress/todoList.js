describe("Automation exercise with Cypress", () => {
    before(() => {
        cy.visit("https://todolistme.net/")
    })
    
    it("Copy the first list and edit the copied name", () => {
        let listName = "Minha nova lista"
        cy.get("ul.categorycontainer ").children().as("category-children")
        cy.get("@category-children").first().find(".copylist").click({force: true})
        cy.get("#updatebox").type(listName).type("{enter}")
        cy.get("@category-children").children().should("contain", listName)
    })
    
    it ("Remove the first list", () => {
        cy.get("ul.categorycontainer ").children().as("category-children")
        cy.get("@category-children").first().as("first-child").find(".listname").invoke("text").then((text) => {
            cy.get("@first-child").find(".delete").click({force: true})
            cy.get("@category-children").should("not.contain", text)
        })
    })
    
    it("Add a new category and then edit it", () => {
        let newCategory = "Minha nova categoria", editCategory = "A melhor categoria"
        cy.get(".adddivider").click()
        cy.get("#updatebox").type(newCategory).type("{enter}")
        cy.get(".categories").should("contain", newCategory)

        cy.get(".categories").last().dblclick()
        cy.get("#updatebox").type(editCategory).type("{enter}")
        cy.get(".categories").should("contain", editCategory)
    })

    it("Remove all tasks", () => {
        cy.removeAllTasks();
        cy.get("ul#mytodos").children().should("have.length", 0)

        cy.wait(500)
    })

    it("Add new tasks", () => {
        let tasks = [ "Levar o lixo para fora.", 
                      "Elaborar o desafio do Cypress.", 
                      "Comprar um livro novo",
                      "Realizar minha parte no código" ]

        cy.get("ul#mytodos").then((mytodos) => {
            let initialLength = mytodos.children().length
        
            tasks.forEach(task => {
                cy.get("#additempanel").type(task).type("{enter}")
            }) 
    
            cy.get("ul#mytodos").children().should("have.length", initialLength + tasks.length)
        })
    })

    it("Edit tasks, given that there are at least 4 elements in the list", () => {
        let editTasks = [ "Cozinhar o jantar.", 
                          "Continuar elaborando o desafio de Cypress",
                          "Continuar a leitura do meu livro.",
                          "Resolver aquele probleminha no código." ]

        editTasks.forEach((task, i)  => {
            cy.get("ul#mytodos").children(`#todo_${i}`).as("target-todo").dblclick()
            cy.get("#updatebox").type(task).type("{enter}")
            cy.get("@target-todo").should("contain", task)
        })
    })

    it("Marks all tasks as completed, given that there is at least one task", () => {
        cy.get("ul#mytodos").children().its("length").then((length) => {
            cy.get("ul#mytodos").children().each(() => {
                cy.get("[type=checkbox]").check({force: true})
            })

            cy.get("ul#mytodos").children().should("have.length", 0)
            cy.get("ul#mydonetodos").children().should("have.length", length)
        })
    })
})