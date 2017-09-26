#include "gwidget.h"
#include "entity.h"
#include "process.h"
#include "edge.h"
#include "mainwindow.h"
#include "Command.h"

QList<CCommand> GraphWidget::script() const
{
	QList<CCommand> commands;
		
	commands.append(sort_by_name(s_get_environmental_params())); // load environmental parameters
	commands.append(sort_by_name(s_get_params())); //load charachterictics of unknown parameters *
	commands.append(sort_by_name(s_get_observed())); // load properties of observed data *
	commands.append(sort_by_name(s_get_model_blocks())); // load model structure (blocks)
	commands.append(sort_by_name(s_get_model_connectors())); // load model structure (connectors)
	commands.append(sort_by_name(s_get_particle_types())); // load particle types *
	commands.append(sort_by_name(s_get_constituents())); // load constituent properties *
	commands.append(sort_by_name(s_get_reactions())); // load reaction network
	commands.append(sort_by_name(s_get_buildup())); // load buildup properties *
	commands.append(sort_by_name(s_get_external_flux())); // load External fluxes *
	commands.append(sort_by_name(s_get_genetic_algorithm())); // load genetic algorithm parameters *
	commands.append(sort_by_name(s_get_MCMC())); // load MCMC parameters *
	commands.append(sort_by_name(s_get_evapotranspiration())); // load evaportranspiration parameters *
	
	return commands; 
}

QList<CCommand> GraphWidget::s_get_params() const
{
	QList<CCommand> commands;
	commands.append(QString("//Parameters"));

	for each (Entity *e in entitiesByType("Parameter"))
	{
		CCommand command;
		command.add_command(e);
		log(command.toQString());
		commands.append(command);
	}
	return commands;
}

QList<CCommand> GraphWidget::s_get_observed() const
{
	QList<CCommand> commands;
	commands.append(QString("//Observations"));
	
	for each (Entity *e in entitiesByType("Observation"))
	{
		CCommand command;
		command.add_command(e);
		log(command.toQString());
		commands.append(command);
	}
	return commands;
}

QList<CCommand> GraphWidget::s_get_environmental_params() const
{
	QList<CCommand> commands;
	commands.append(QString("//Project/Climate/Solver settings"));
	QList<Entity*> list;
	list.append(entitiesByType("Project settings"));
	list.append(entitiesByType("Climate settings"));
	list.append(entitiesByType("Solver settings"));

	for each (Entity *e in list)
	{
		CCommand command;
		command.command = "setprop";
		command.values.append(e->Name());
		for each (mProp prop in e->getmList(e->objectType).List)
		{
			if (!e->val(prop.VariableCode).isEmpty() && e->val(prop.VariableCode) != "Default")
				if (e->val(prop.VariableCode).replace("...", "").trimmed()!="")
				{
					XString val = e->getValue(prop.VariableName);
					command.parameters[XString::reformBack(prop.VariableName)] = val.replace("...", "");
					command.parameters[XString::reformBack(prop.VariableName)].unit = val.unit;
				}
		}
		log(command.toQString());
		commands.append(command);
	}
	return commands; 
}

QList<CCommand> GraphWidget::s_get_model_blocks() const
{
	QList<CCommand> commands;
	commands.append(QString("//Nodes"));
	for each(Node *n in Nodes())
	{
		CCommand command;
		command.add_command(n);
		log(command.toQString());
		commands.append(command);
	}
	return commands;
}

QList<CCommand> GraphWidget::s_get_model_connectors() const
{
	QList<CCommand> commands;
	commands.append(QString("//Connectors"));
	for each(Edge *e in Edges())
	{
		CCommand command;
		command.add_command(e);
		log(command.toQString());
		commands.append(command);
	}
	
	return commands; 
}

QList<CCommand> GraphWidget::s_get_particle_types() const
{
	QList<CCommand> commands;
	for each (Entity *n in entitiesByType("Particle"))
	{

		CCommand command;
		command.add_command(n);
		log(command.toQString());
		commands.append(command);
	}
	
	return commands;
}

QList<CCommand> GraphWidget::s_get_buildup() const
{
	QList<CCommand> commands;
	for each (Entity *n in entitiesByType("Build-up"))
	{

		CCommand command;
		command.add_command(n);
		log(command.toQString());
		commands.append(command);
	}
	return commands;
}

QList<CCommand> GraphWidget::s_get_evapotranspiration() const
{
	QList<CCommand> commands;
	for each (Entity *n in entitiesByType("Evapotranspiration"))
	{

		CCommand command;
		command.add_command(n);
		log(command.toQString());
		commands.append(command);
	}
	return commands;
}

QList<CCommand> GraphWidget::s_get_MCMC() const
{
	QList<CCommand> commands;
	for each (Entity *n in entitiesByType("Markov chain Monte Carlo"))
	{

		CCommand command;
		command.add_command(n);
		log(command.toQString());
		commands.append(command);
	}
	return commands;
}

QList<CCommand> GraphWidget::s_get_genetic_algorithm() const
{
	QList<CCommand> commands;
	for each (Entity *n in entitiesByType("Genetic algorithm"))
	{

		CCommand command;
		command.add_command(n);
		log(command.toQString());
		commands.append(command);
	}
	return commands;
}



QList<CCommand> GraphWidget::s_get_external_flux() const
{
	QList<CCommand> commands;
	for each (Entity *n in entitiesByType("External Flux"))
	{

		CCommand command;
		command.add_command(n);
		log(command.toQString());
		commands.append(command);
	}
	return commands;
}

QList<CCommand> GraphWidget::s_get_constituents() const
{
	QList<CCommand> commands;
	for each (Entity *n in entitiesByType("Constituent"))
	{

		CCommand command;
		command.add_command(n);
		log(command.toQString());
		commands.append(command);
	}
	
	return commands;
	
}

QList<CCommand> GraphWidget::s_get_reactions() const
{
	QList<CCommand> commands;
	for each (Entity *n in entitiesByType("Reaction parameter"))
	{
		CCommand command;
		command.add_command(n);
		log(command.toQString());
		commands.append(command);
	}
	for each (Process *e in Processes)
	{
		CCommand command;
		command.command = "add";
		command.values.append("'Reaction");
		command.parameters["Rate"] = e->rateExpression();

		for each (QString key in e->productExpressions().keys())
			command.parameters[QString("prod[%1]").arg(key)] = e->productExpressions()[key];
		
		log(command.toQString());
		commands.append(command);
	}
	return commands;
}
