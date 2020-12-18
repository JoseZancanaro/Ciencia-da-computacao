import React, { useState, useEffect } from 'react'
import {
  makeStyles,
  AppBar,
  Toolbar,
  Drawer,
  Button,
  List,
  Typography,
  ListItem,
  ListItemIcon,
  ListItemText,
  Box,
  Grid,
  Hidden,
  Switch,
} from '@material-ui/core'

import axios from 'axios'

import BugReportIcon from '@material-ui/icons/BugReport'
import DashboardIcon from '@material-ui/icons/Dashboard'
import RefreshIcon from '@material-ui/icons/Refresh'
import Whatshot from '@material-ui/icons/Whatshot'

const endpoint = 'http://localhost:3301/watch/sensor'
const drawerWidth = 240

const useStyles = makeStyles((theme) => ({
  root: {
    height: '100%',
    backgroundColor: theme.palette.background.dark,
  },
  appBar: {
    //boxShadow: 'none',
    zIndex: theme.zIndex.drawer + 1
  },
  logo: {
    marginLeft: theme.spacing(3)
  },
  drawer: {
    width: drawerWidth,
    flexShrink: 0,
  },
  drawerPaper: {
    width: drawerWidth,
    borderRight: 'none',
  },
  drawerContainer: {
    overflow: 'auto',
  },
  icons: {
    paddingRight: theme.spacing(5),
  },
  grow: {
    flexGrow: 1,
  },
  listItemText: {
    fontSize: 14,
  },
  listItem: {
    paddingTop: 4,
    paddingBottom: 4,
  },
  subheader: {
    textTransform: 'uppercase',
  },
}))

function Home({ darkMode, setDarkMode }) {
  const [ sensors, setSensors ] = useState([])
  const classes = useStyles()

  async function fetchData() {
    const response = await axios.get(endpoint)
    setSensors(response.data)
  }

  useEffect(() => {
    fetchData()
  }, [])

  return (
    <div className={classes.root}>
      <AppBar color='inherit' className={classes.appBar}>
        <Toolbar>
          <DashboardIcon color='secondary' className={classes.logo} />
          <Typography
            variant='subtitle1'
            color='textPrimary'
            style={{ paddingLeft: 10, fontWeight: 600}}
          >
            Dashboard
          </Typography>

          <div className={classes.grow} />
          <Switch
            value={darkMode}
            onChange={() => setDarkMode(!darkMode)}
            className={classes.icons}
          />
          <Button
            startIcon={<RefreshIcon />}
            variant='outlined'
            color='secondary'
            onClick={() => fetchData()}
          >
            Refresh
          </Button>
        </Toolbar>
      </AppBar>
      <Box display='flex'>
        <Hidden mdDown>
          <Drawer
            className={classes.drawer}
            variant='permanent'
            classes={{
              paper: classes.drawerPaper,
            }}
          >
            <Toolbar />
            <div className={classes.drawerContainer}>
              <List>
                <ListItem button classes={{ root: classes.listItem }}>
                  <ListItemIcon>{<Whatshot />}</ListItemIcon>
                  <ListItemText
                    classes={{
                      primary: classes.listItemText,
                    }}
                    primary='Watcher'
                  />
                </ListItem>
              </List>
            </div>
          </Drawer>
        </Hidden>

        <Box className={classes.grow} p={8}>
          <Toolbar />
          <Typography
            variant='h5'
            color='textPrimary'
            style={{ fontWeight: 600, marginBottom: '20px' }}
          >
            Sensores
          </Typography>

          <Grid container spacing={4}>
            {sensors.map((item, index) => (
                <Grid item lg={3} md={4} sm={6} xs={12}>
                  <Box>
                    <BugReportIcon style={{ height: '25px' }}/>
                    <Box>
                      <Typography
                        style={{ fontWeight: 600 }}
                        gutterBottom
                        variant='body1'
                        color='textPrimary'
                      >
                        {`${item.zip} ${item.order}`}
                      </Typography>
                      <Typography
                        display='block'
                        variant='body2'
                        color='textSecondary'
                      >
                        {`${item.lat} ${item.lng}`}
                      </Typography>
                      {
                        item.readings.length &&
                        <>
                          <Typography variant='body2' color='textSecondary'>
                            {`Healthy: ${item.readings[0].healthy} • Problem: ${item.readings[0].bad_section ? item.readings[0].source_of_failure : 'No problem'}`}
                          </Typography>
                          <Typography variant='body2' color='textSecondary'>
                            {`Flow ${item.readings[0].flow} • Pressure ${item.readings[0].pressure} Height ${item.readings[0].height}`}
                          </Typography>
                        </>
                      }
                      {
                        !item.readings.length &&
                        <>
                          <Typography variant='body2' color='textSecondary'>
                            {`No Data`}
                          </Typography>
                        </>
                      }
                    </Box>
                  </Box>
                </Grid>
              ))}
          </Grid>
        </Box>
      </Box>
    </div>
  )
}

export default Home